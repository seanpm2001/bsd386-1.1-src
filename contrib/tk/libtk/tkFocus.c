/* 
 * tkFocus.c --
 *
 *	This file contains procedures that manage the input
 *	focus for Tk.
 *
 * Copyright (c) 1990-1993 The Regents of the University of California.
 * All rights reserved.
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that the
 * above copyright notice and the following two paragraphs appear in
 * all copies of this software.
 * 
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF
 * CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 */

#ifndef lint
static char rcsid[] = "$Header: /bsdi/MASTER/BSDI_OS/contrib/tk/libtk/tkFocus.c,v 1.1.1.1 1994/01/03 23:15:24 polk Exp $ SPRITE (Berkeley)";
#endif

#include "tkInt.h"
#include "tkConfig.h"

/*
 * Magic value stored in "send_event" field to mark a FocusIn or FocusOut
 * event generated by this file.  It indicates to TkFilterFocusEvent that
 * it shouldn't process this event.
 */

#define GENERATED_EVENT 0x123abcde

/*
 * Forward declarations for procedures defined in this file:
 */

static void		ChangeFocusTopLevelPtr _ANSI_ARGS_((TkDisplay *dispPtr,
			    TkWindow *winPtr, int mode));
static void		QueueFocusEvent _ANSI_ARGS_((TkWindow *winPtr,
			    int type, int mode, int detail));
static void		SetFocus _ANSI_ARGS_((TkWindow *winPtr,
			    TkWindow *focusPtr));

/*
 *--------------------------------------------------------------
 *
 * Tk_CreateFocusHandler --
 *
 *	Arrange for a procedure to be called whenever the focus
 *	enters or leaves a given window.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	After this procedure has been invoked, whenever tkwin gets
 *	or loses the input focus, proc will be called.  It should have
 *	the following structure:
 *
 *	void
 *	proc(clientData, gotFocus)
 *	    ClientData clientData;
 *	    int gotFocus;
 *	{
 *	}
 *
 *	The clientData argument to "proc" will be the same as the
 *	clientData argument to this procedure.  GotFocus will be
 *	1 if tkwin is getting the focus, and 0 if it's losing the
 *	focus.
 *
 *--------------------------------------------------------------
 */

void
Tk_CreateFocusHandler(tkwin, proc, clientData)
    Tk_Window tkwin;		/* Token for window. */
    Tk_FocusProc *proc;		/* Procedure to call when tkwin gets
				 * or loses the input focus. */
    ClientData clientData;	/* Arbitrary value to pass to proc. */
{
    register TkWindow *winPtr = (TkWindow *) tkwin;

    winPtr->focusProc = proc;
    winPtr->focusData = clientData;
}

/*
 *--------------------------------------------------------------
 *
 * Tk_FocusCmd --
 *
 *	This procedure is invoked to process the "focus" Tcl command.
 *	See the user documentation for details on what it does.
 *
 * Results:
 *	A standard Tcl result.
 *
 * Side effects:
 *	See the user documentation.
 *
 *--------------------------------------------------------------
 */

int
Tk_FocusCmd(clientData, interp, argc, argv)
    ClientData clientData;	/* Main window associated with
				 * interpreter. */
    Tcl_Interp *interp;		/* Current interpreter. */
    int argc;			/* Number of arguments. */
    char **argv;		/* Argument strings. */
{
    Tk_Window tkwin = (Tk_Window) clientData;
    register TkWindow *winPtr = (TkWindow *) clientData;
    register TkWindow *newPtr;
    char c;
    int length;

    /*
     * If invoked with no arguments, just return the current focus window.
     */

    if (argc == 1) {
	if (winPtr->mainPtr->focusPtr == NULL) {
	    interp->result = "none";
	} else {
	    interp->result = winPtr->mainPtr->focusPtr->pathName;
	}
	return TCL_OK;
    }

    /*
     * If invoked with a single argument beginning with "." then focus
     * on that window.
     */

    if ((argc == 2) && (argv[1][0] == '.')) {
	newPtr = (TkWindow *) Tk_NameToWindow(interp, argv[1], tkwin);
	if (newPtr == NULL) {
	    return TCL_ERROR;
	}
	SetFocus(winPtr, newPtr);
	return TCL_OK;
    }

    length = strlen(argv[1]);
    c = argv[1][0];
    if ((c == 'd') && (strncmp(argv[1], "default", length) == 0)) {
	if (argc > 3) {
	    Tcl_AppendResult(interp, "wrong # args: should be \"",
		    argv[0], " default ?window?\"", (char *) NULL);
	    return TCL_ERROR;
	}
	if (argc == 2) {
	    if (winPtr->mainPtr->focusDefaultPtr == NULL) {
		interp->result = "none";
	    } else {
		interp->result = winPtr->mainPtr->focusDefaultPtr->pathName;
	    }
	    return TCL_OK;
	}
	if ((argv[2][0] == 'n')
		&& (strncmp(argv[2], "none", strlen(argv[2])) == 0)) {
	    newPtr = NULL;
	} else {
	    newPtr = (TkWindow *) Tk_NameToWindow(interp, argv[2], tkwin);
	    if (newPtr == NULL) {
		return TCL_ERROR;
	    }
	}
	winPtr->mainPtr->focusDefaultPtr = newPtr;
    } else if ((c == 'n') && (strncmp(argv[1], "none", length) == 0)) {
	if (argc != 2) {
	    Tcl_AppendResult(interp, "wrong # args: should be \"",
		    argv[0], " none\"", (char *) NULL);
	    return TCL_ERROR;
	}
	SetFocus(winPtr, (TkWindow *) NULL);
    } else {
	Tcl_AppendResult(interp, "bad option \"", argv[1],
		"\": must be default or none", (char *) NULL);
	return TCL_ERROR;
    }
    return TCL_OK;
}

/*
 *--------------------------------------------------------------
 *
 * TkFocusFilterEvent --
 *
 *	This procedure is invoked by Tk_HandleEvent when it encounters
 *	a FocusIn, FocusOut, Enter, or Leave event.
 *
 * Results:
 *	A return value of 1 means that Tk_HandleEvent should process
 *	the event normally (i.e. event handlers should be invoked).
 *	A return value of 0 means that this event should be ignored.
 *
 * Side effects:
 *	An additional event may be generated and processed.
 *
 *--------------------------------------------------------------
 */

int
TkFocusFilterEvent(winPtr, eventPtr)
    register TkWindow *winPtr;	/* Window that focus event is directed to. */
    XEvent *eventPtr;		/* FocusIn or FocusOut event. */
{
    if ((eventPtr->type == FocusIn) || (eventPtr->type == FocusOut)) {
	/*
	 * If this event was generated by us then just process it
	 * normally.
	 */

	if (eventPtr->xfocus.send_event == GENERATED_EVENT) {
	    eventPtr->xfocus.send_event = 1;
	    return 1;
	}

	/*
	 * Ignore the focus event if any of the following things is
	 * true:
	 *
	 * 1. The event isn't for a top-level window.
	 * 2. The event has detail NotifyInferior (which means the
	 *    focus moved around within the top-level window;  it
	 *    didn't move between the top-level window and the
	 *    outside world.
	 * 3. The event has detail NotifyPointer (I don't really understand
	 *    what these events are for, but they don't seem to serve
	 *    any useful purpose).
	 */

	if (!(winPtr->flags & TK_TOP_LEVEL)
		|| (eventPtr->xfocus.detail == NotifyInferior)
		|| (eventPtr->xfocus.detail == NotifyPointer)) {
	    return 0;
	}

	/*
	 * This is a useful event.  Notify both the top-level window
	 * and the window that has been assigned the focus by the Tk
	 * "focus" command.
	 */

	if (eventPtr->type == FocusOut) {
	    ChangeFocusTopLevelPtr(winPtr->dispPtr, (TkWindow *) NULL,
		    eventPtr->xfocus.mode);
	} else {
	    ChangeFocusTopLevelPtr(winPtr->dispPtr, winPtr,
		    eventPtr->xfocus.mode);
	}
    
	/*
	 * This particular event should now be ignored, since we just
	 * generated events to notify all of the relevant windows.
	 */
    
	return 0;
    } else {
	/*
	 * This is an Enter or Leave event.  If there's no window manager,
	 * or if the window manager is not moving the focus around (e.g.
	 * if the disgusting "NoTitleFocus" option has been selected in
	 * twm), then we won't get FocusIn or FocusOut events.  Instead,
	 * watch enter and leave events.  If an Enter event arrives for a
	 * top-level window with its focus field set, but we don't have a
	 * record of a FocusIn event, then simulate one.  If a Leave event
	 * arrives and focus was set for the window via an Enter event,
	 * then simulate a FocusOut event.
	 */

	if ((eventPtr->type == EnterNotify) && (winPtr->flags & TK_TOP_LEVEL)
		&& eventPtr->xcrossing.focus
		&& (eventPtr->xcrossing.detail != NotifyInferior)
		&& (winPtr->dispPtr->focusTopLevelPtr != winPtr)) {
	    ChangeFocusTopLevelPtr(winPtr->dispPtr, winPtr,
		    eventPtr->xcrossing.mode);
	    winPtr->dispPtr->focussedOnEnter = 1;
	} else if ((eventPtr->type == LeaveNotify)
		&& (winPtr->dispPtr->focussedOnEnter)
		&& (eventPtr->xcrossing.detail != NotifyInferior)
		&& (winPtr->dispPtr->focusTopLevelPtr == winPtr)) {
	    ChangeFocusTopLevelPtr(winPtr->dispPtr, (TkWindow *) NULL,
		    eventPtr->xcrossing.mode);
	}
	return 1;
    }
}

/*
 *----------------------------------------------------------------------
 *
 * ChangeFocusTopLevelPtr --
 *
 *	This procedure is invoked to change the focusTopLevelPtr field
 *	of a display.  It notifies the old focus window, if any, and
 *	the new one.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Windows get notified, and they can do just about anything
 *	as part of the notification.
 *
 *----------------------------------------------------------------------
 */

static void
ChangeFocusTopLevelPtr(dispPtr, winPtr, mode)
    TkDisplay *dispPtr;			/* Display whose focus top-level
					 * changed. */
    TkWindow *winPtr;			/* Top-level window that is to be the
					 * new focus top-level for display.
					 * If NULL, clears the old focus
					 * window without setting a new one. */
    int mode;				/* Mode to use for generated events:
					 * NotifyNormal, NotifyGrab, or
					 * NotifyUngrab. */
{
    TkWindow *focusPtr;

    if (dispPtr->focusTopLevelPtr == winPtr) {
	/*
	 * The focus is already where it's supposed to be, so there's
	 * nothing else to do.
	 */
	return;
    }

    if (dispPtr->focusTopLevelPtr != NULL) {
	focusPtr = dispPtr->focusTopLevelPtr->mainPtr->focusPtr;
	if (focusPtr != NULL) {
	    QueueFocusEvent(focusPtr, FocusOut, mode, NotifyAncestor);
	}
	QueueFocusEvent(dispPtr->focusTopLevelPtr, FocusOut, mode,
		NotifyVirtual);
    }
    if (winPtr != NULL) {
	focusPtr = winPtr->mainPtr->focusPtr;
	QueueFocusEvent(winPtr, FocusIn, mode, NotifyVirtual);
	if (focusPtr != NULL) {
	    QueueFocusEvent(focusPtr, FocusIn, mode, NotifyAncestor);
	}
    }
    dispPtr->focusTopLevelPtr = winPtr;
    dispPtr->focussedOnEnter = 0;
}

/*
 *----------------------------------------------------------------------
 *
 * SetFocus --
 *
 *	This procedure is invoked to change the focus window for
 *	an application.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Event handlers may be invoked to process the change of
 *	focus.
 *
 *----------------------------------------------------------------------
 */

static void
SetFocus(winPtr, focusPtr)
    TkWindow *winPtr;		/* Window that identifies the application
				 * whose focus is to change. */
    TkWindow *focusPtr;		/* Window that is to be the new focus for
				 * the application.  May be NULL. */
{
    if (winPtr->mainPtr->focusPtr == focusPtr) {
	return;
    }
    if ((winPtr->dispPtr->focusTopLevelPtr != NULL) &&
	    (winPtr->mainPtr == winPtr->dispPtr->focusTopLevelPtr->mainPtr)) {
	if (winPtr->mainPtr->focusPtr != NULL) {
	    QueueFocusEvent(winPtr->mainPtr->focusPtr, FocusOut,
		    NotifyNormal, NotifyAncestor);
	}
	if (focusPtr != NULL) {
	    QueueFocusEvent(focusPtr, FocusIn, NotifyNormal, NotifyAncestor);
	}
    }
    winPtr->mainPtr->focusPtr = focusPtr;
}

/*
 *----------------------------------------------------------------------
 *
 * QueueFocusEvent --
 *
 *	This procedure implements the mechanics of notifying a window
 *	that has just gotten or lost the focus.  It generates an
 *	appropriate X event, queues it to be process before any other
 *	events from the server (but after any other queued events),
 *	and also uses the (now obsolete) mechanism of calling a focus
 *	procedure.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Depends on the actions associated with the focus event and
 *	procedure callback.
 *
 *----------------------------------------------------------------------
 */

static void
QueueFocusEvent(winPtr, type, mode, detail)
    TkWindow *winPtr;		/* Window that's getting or losing focus. */
    int type;			/* FocusIn or FocusOut:  tells whether
				 * winPtr is getting or losing the focus. */
    int mode;			/* Mode to use for event: NotifyNormal,
				 * NotifyGrab, or NotifyUngrab. */
    int detail;			/* Detail to use for event:  NotifyAncestor
				 * for the ultimate destination of the focus,
				 * and NotifyVirtual for the top-level window
				 * that actually got the X focus. */
{
    XEvent event;

    if (winPtr->flags & TK_ALREADY_DEAD) {
	/*
	 * Window is in the process of being destroyed so quit (otherwise
	 * the code below may recreate the window!).
	 */
	return;
    }
    Tk_MakeWindowExist((Tk_Window) winPtr);

    /*
     * Generate an event for the focus change and process the event.
     */

    event.type = type;
    event.xfocus.serial = LastKnownRequestProcessed(winPtr->display);
    event.xfocus.send_event = GENERATED_EVENT;
    event.xfocus.display = winPtr->display;
    event.xfocus.window = winPtr->window;
    event.xfocus.mode = mode;
    event.xfocus.detail = detail;
    TkQueueEvent(winPtr->dispPtr, &event);

    if ((detail == NotifyAncestor) && (winPtr->focusProc != NULL)) {
	(*winPtr->focusProc)(winPtr->focusData, (type == FocusIn));
    }
}

/*
 *----------------------------------------------------------------------
 *
 * TkFocusDeadWindow --
 *
 *	This procedure is invoked when it is determined that
 *	a window is dead.  It cleans up focus-related information
 *	about the window.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Various things get cleaned up and recycled.
 *
 *----------------------------------------------------------------------
 */

void
TkFocusDeadWindow(winPtr)
    register TkWindow *winPtr;		/* Information about the window
					 * that is being deleted. */
{
    if (winPtr->mainPtr != NULL) {
	if (winPtr->mainPtr->focusDefaultPtr == winPtr) {
	    winPtr->mainPtr->focusDefaultPtr = NULL;
	}
	if (winPtr->mainPtr->focusPtr == winPtr) {
	    SetFocus(winPtr, winPtr->mainPtr->focusDefaultPtr);
	}
    }
    if (winPtr->dispPtr->focusTopLevelPtr == winPtr) {
	winPtr->dispPtr->focusTopLevelPtr = NULL;
    }
}
