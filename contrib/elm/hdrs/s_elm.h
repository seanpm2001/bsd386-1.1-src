/* s_elm.h created from s_elm.us by gencat on Tue Aug  3 14:58:35 EDT 1993 */

#define ElmSet	0x3
#define ElmYes	0x1
#define ElmNo	0x2
#define ElmAliasUnknown	0x3
#define ElmCannotExpandNoCR	0x4
#define ElmUseCheckalias	0x5
#define ElmUnknownAddress	0x6
#define ElmCantBuildRetAddr	0x7
#define Elmitem	0x8
#define Elmitems	0x9
#define ElmItem	0xa
#define ElmItems	0xb
#define ElmPrompt	0xc
#define ElmInitInternalTables	0xd
#define ElmErrorExpanding	0xf
#define ElmIllegalAddress	0x10
#define ElmAliasExpTooLong	0x11
#define ElmMoreUser0	0x12
#define ElmMoreUser0Plural	0x13
#define ElmMoreUser1	0x14
#define ElmMoreUser1Plural	0x15
#define ElmMoreUser2	0x16
#define ElmMoreUser2Plural	0x17
#define ElmTitleDeleted	0x18
#define ElmTitleForm	0x19
#define ElmTitleMessage	0x1a
#define ElmTitleTo	0x1b
#define ElmTitleFrom	0x1c
#define ElmTitlePage	0x1d
#define ElmNoDelSysAlias	0x1e
#define ElmNoPathTo	0x1f
#define ElmPermFolder	0x20
#define ElmInvokeEditor	0x21
#define ElmProblemsInvokingEditor	0x22
#define ElmWarnNewMailRecv	0x23
#define ElmCouldntReopenTemp	0x24
#define ElmCouldntOpenFolder	0x25
#define ElmCouldntSeekEnd	0x26
#define ElmCouldntCopyMailfile	0x27
#define ElmCheckOutMail	0x28
#define ElmCouldntLinkMailfile	0x29
#define ElmProblemsRestoringPerms	0x2a
#define ElmChangesIncorporated	0x2b
#define ElmResyncingNewVersion	0x2c
#define ElmCantInvokeEditor	0x2d
#define ElmSimpleContinue	0x2e
#define ElmPostEdContinue	0x2f
#define ElmCouldntOpenAppend	0x30
#define ElmContinueEntering	0x31
#define ElmEnterMessage	0x32
#define ElmTypeElmCommands	0x33
#define ElmCommandsInclude	0x34
#define ElmCantFindEmacs	0x35
#define ElmDontKnowEmacs	0x36
#define ElmEnterNameEditor	0x37
#define ElmUseSpecificCommand	0x38
#define ElmDontKnowChar	0x39
#define ElmEndOfMessage	0x3a
#define ElmEditmsgAvailOpts	0x3b
#define ElmEditmsgHelpMenu	0x3c
#define ElmEditmsgAddLine	0x3d
#define ElmEditmsgBCC	0x3e
#define ElmEditmsgCC	0x3f
#define ElmEditmsgEmacs	0x40
#define ElmEditmsgAddMessage	0x41
#define ElmEditmsgToCCBCC	0x42
#define ElmEditmsgSameCurrentPrefix	0x43
#define ElmEditmsgUserEditor	0x44
#define ElmEditmsgPrintMsg	0x45
#define ElmEditmsgReadFile	0x46
#define ElmEditmsgSubject	0x47
#define ElmEditmsgTo	0x48
#define ElmEditmsgVi	0x49
#define ElmEditmsgUnixCmd	0x4a
#define ElmEditmsgAddUnixCmd	0x4b
#define ElmEditmsgEndMsg	0x4c
#define ElmEditmsgContinue	0x4d
#define ElmNoFilenameSpecified	0x4e
#define ElmCouldntReadFile	0x4f
#define ElmAddedLine	0x50
#define ElmAddedLinePlural	0x51
#define ElmAddedChar	0x52
#define ElmAddedCharPlural	0x53
#define ElmAddedFromFile	0x54
#define ElmAddedToMessage	0x55
#define ElmEditmsgPrintTo	0x57
#define ElmEditmsgPrintCC	0x58
#define ElmEditmsgPrintBCC	0x59
#define ElmEditmsgPrintSubject	0x5a
#define ElmEditmsgPrintContinue	0x5c
#define ElmNoMessageReadContinue	0x5d
#define ElmValidNumbersBetween	0x5e
#define ElmCantFindReadmsg	0x5f
#define ElmEditmsgCouldntAdd	0x60
#define ElmEditmsgOneMoreCancel	0x61
#define ElmEditmsgCancelled	0x62
#define ElmDecryptPrompt	0x63
#define ElmFirstEncryptPrompt	0x64
#define ElmSecondEncryptPrompt	0x65
#define ElmKeysNotSame	0x66
#define ElmAbandonChange	0x67
#define ElmAbandonChangePlural	0x68
#define ElmSendOnlyMode	0x69
#define ElmNewMailHangOn	0x6a
#define ElmCantOpenFolderRead	0x6b
#define ElmNewMessageRecv	0x6c
#define ElmNewMessageRecvPlural	0x6d
#define ElmResyncFolder	0x6e
#define ElmNoMailToPipe	0x6f
#define ElmNoMailReturnAddress	0x70
#define ElmNoMailToScan	0x71
#define ElmPatternNotFound	0x72
#define ElmScanForCalendar	0x73
#define ElmSorryNoCalendar	0x74
#define ElmBounceMessage	0x75
#define ElmNoMailToBounce	0x76
#define ElmChangeFolder	0x77
#define ElmEditFolder	0x78
#define ElmFolderIsEmpty	0x79
#define ElmNoFolderEdit	0x7a
#define ElmForward	0x7b
#define ElmNoMailToForward	0x7c
#define ElmGroupReply	0x7d
#define ElmCantGroupReplyForm	0x7e
#define ElmNoMailToReply	0x7f
#define ElmMessageWithHeaders	0x80
#define ElmDisplayMessage	0x81
#define ElmNoMailToRead	0x82
#define ElmLimitDisplayBy	0x83
#define ElmMail	0x84
#define ElmNextMessage	0x85
#define ElmOptions	0x86
#define ElmPrintMail	0x87
#define ElmNoMailToPrint	0x88
#define ElmQuit	0x89
#define ElmNewMailQuitCancelled	0x8a
#define ElmQuickQuit	0x8b
#define ElmNewMailQuickQuitCancelled	0x8c
#define ElmReplyToMessage	0x8d
#define ElmNoMailToReplyTo	0x8e
#define ElmNoMailToSave	0x8f
#define ElmNoMailToCopy	0x90
#define ElmSaveToFolder	0x91
#define ElmCopyToFolder	0x92
#define ElmQuickExit	0x93
#define ElmExit	0x94
#define ElmExpandsTo	0x95
#define ElmAlreadyOnLastPage	0x96
#define ElmAlreadyOnFirstPage	0x97
#define ElmNoItemToDelete	0x98
#define ElmNoMoreItemBelow	0x99
#define ElmNoItemUndeletedBelow	0x9a
#define ElmNoMailInFolder	0x9b
#define ElmNoAliases	0x9c
#define ElmNoMoreItemAbove	0x9d
#define ElmNoMoreUndeletedAbove	0x9e
#define ElmNoItemToTag	0x9f
#define ElmNoItemToMarkUndeleted	0xa0
#define ElmNoItemToUndelete	0xa1
#define ElmNewCurrentItem	0xa2
#define ElmNotThatMany	0xa3
#define ElmNotInLimitedDisplay	0xa4
#define ElmUnknownCommand	0xa5
#define ElmUseForHelp	0xa6
#define ElmNoMailToCheck	0xa7
#define ElmFileHelpmsg1	0xa8
#define ElmFileHelpmsg2	0xa9
#define ElmFileHelpmsg3	0xaa
#define ElmFileHelpmsg4	0xab
#define ElmFileHelpmsg5	0xac
#define ElmFileHelpmsg6	0xad
#define ElmFileHelpmsg7	0xae
#define ElmFileHelpmsg8	0xaf
#define ElmSave	0xbd
#define ElmCopy	0xbe
#define ElmCapSave	0xbf
#define ElmCapCopy	0xc0
#define ElmSaved	0xc1
#define ElmCopied	0xc2
#define ElmSaveMessageTo	0xc3
#define ElmSaveMessagesTo	0xc4
#define ElmCannotSaveMessage	0xc5
#define ElmCouldntAppendFolder	0xc6
#define ElmMessageSaved	0xc7
#define ElmMessagesSaved	0xc8
#define ElmMessageAppendedFolder	0xc9
#define ElmMessageSavedFolder	0xca
#define ElmDontKnowHomeCursor	0xcb
#define ElmDontKnowHomePrintf	0xcc
#define ElmDontKnowValueCursor	0xcd
#define ElmDontKnowValuePrintf	0xce
#define ElmErrorFstat	0xcf
#define ElmCouldNotOpenFile	0xd0
#define ElmWriteFailedCopy	0xd1
#define ElmCloseFailedCopy	0xd2
#define ElmWriteFailedAppend	0xd3
#define ElmCloseFailedAppend	0xd4
#define ElmNoPermRead	0xd5
#define ElmNoMail	0xd6
#define ElmMailBeingForwarded	0xd7
#define ElmSeekFailed	0xd8
#define ElmWriteCopyMessageFailed	0xd9
#define ElmErrorOpeningCheckFields	0xda
#define ElmCantReadMessageToValidate	0xdb
#define ElmCouldntOpenNewformOutput	0xdc
#define ElmErrorUnlinkingFile	0xdd
#define ElmErrorLinkingFile	0xde
#define ElmSeekFailedFile	0xdf
#define ElmNoFormInMessage	0xe0
#define ElmBadForm	0xe1
#define ElmCantOpenAsOutputFile	0xe2
#define ElmEnterAsManyLines	0xe3
#define ElmFormNoPrompt	0xe4
#define ElmHdrmenuScreenTitle	0xe5
#define ElmHdrmenuInstruct	0xe6
#define ElmHdrmenuInstructNoShell	0xe7
#define ElmHdrmenuPrompt	0xe8
#define ElmHdrmenuBadChoice	0xe9
#define ElmHdrmenuGetExpiresInstruct	0xea
#define ElmHdrmenuGetUserdefInstruct	0xeb
#define ElmHdrmenuGetInstruct	0xec
#define ElmHdrmenuExpiresNotNumber	0xed
#define ElmHdrmenuExpiresOutOfRange	0xee
#define ElmHdrmenuPrecedenceBadValue	0xef
#define ElmHdrmenuUserdefNotAlnum	0xf0
#define ElmHdrmenuUserdefMissingColon	0xf1
#define ElmHdrmenuDomInstruct	0xf2
#define ElmHdrmenuDomPrompt	0xf3
#define ElmHelpMessage	0xff
#define ElmHelpPrompt	0x100
#define ElmHelpUnknownCommand	0x101
#define ElmHelpSystem	0x102
#define ElmHelpCouldntOpenFile	0x103
#define ElmHelpPressSpaceToContinue	0x104
#define ElmHelpPressAnyKeyToReturn	0x105
#define ElmHelpDollar	0x106
#define ElmHelpShell	0x107
#define ElmHelpDebugSummary	0x108
#define ElmHelpPipe	0x109
#define ElmHelpDebugAll	0x10a
#define ElmHelpDebugReturnAdd	0x10b
#define ElmHelpLastMessage	0x10c
#define ElmHelpPreviousPage	0x10d
#define ElmHelpFirstMessage	0x10e
#define ElmHelpNextScreen	0x10f
#define ElmHelpDisplayCurrent	0x110
#define ElmHelpNextPage	0x111
#define ElmHelpSearchFolder	0x112
#define ElmHelpCalendar	0x113
#define ElmHelpSave	0x114
#define ElmHelpToggleStatus	0x115
#define ElmHelpAliasSubmenu	0x116
#define ElmHelpBounce	0x117
#define ElmHelpCopy	0x118
#define ElmHelpChangeFolder	0x119
#define ElmHelpDelete	0x11a
#define ElmHelpDeletePattern	0x11b
#define ElmHelpEditor	0x11c
#define ElmHelpForward	0x11d
#define ElmHelpGroupReply	0x11e
#define ElmHelpDisplayHeaders	0x11f
#define ElmHelpReturnToIndex	0x120
#define ElmHelpNextMessage	0x121
#define ElmHelpNextUndeleted	0x122
#define ElmHelpPreviousMessage	0x123
#define ElmHelpPreviousUndeleted	0x124
#define ElmHelpLimitDisplay	0x125
#define ElmHelpSendMail	0x126
#define ElmHelpDisplayNext	0x127
#define ElmHelpDisplayThenNext	0x128
#define ElmHelpOptionsMenu	0x129
#define ElmHelpPrint	0x12a
#define ElmHelpQuitPager	0x12b
#define ElmHelpQuitMailer	0x12c
#define ElmHelpReplyMessage	0x12d
#define ElmHelpSaveMessage	0x12e
#define ElmHelpTagMessage	0x12f
#define ElmHelpTagPattern	0x130
#define ElmHelpUndeleteMessage	0x131
#define ElmHelpExitFolder	0x132
#define ElmHelpQuickExit	0x133
#define ElmHelpQuickQuit	0x134
#define ElmHelpScrollForward	0x135
#define ElmHelpDisplayCurrentMessage	0x136
#define ElmHelpRewriteScreen	0x137
#define ElmHelpExitQuickly	0x138
#define ElmHelpMakeMessageCurrent	0x139
#define ElmYouHaveNoPasswordEntry	0x13a
#define ElmCouldNotOpenDebugFile	0x13b
#define ElmNoTerm	0x13c
#define ElmBadTerm	0x13e
#define ElmLeaveDeleteMessage	0x141
#define ElmLeaveDeleteMessages	0x142
#define ElmLeaveMoveMessage	0x143
#define ElmLeaveMoveMessages	0x144
#define ElmLeaveKeepMessage	0x145
#define ElmLeaveKeepMessages	0x146
#define ElmSomethingWrongInCounts	0x147
#define ElmFolderUnchanged	0x148
#define ElmLeaveKeepStoreDelete	0x149
#define ElmLeaveKeepStoreDeletePlural	0x14a
#define ElmLeaveKeepStore	0x14b
#define ElmLeaveKeepStorePlural	0x14c
#define ElmLeaveKeepDelete	0x14d
#define ElmLeaveKeepDeletePlural	0x14e
#define ElmLeaveKeep	0x14f
#define ElmLeaveKeepPlural	0x150
#define ElmLeaveStoreDelete	0x151
#define ElmLeaveStoreDeletePlural	0x152
#define ElmLeaveStore	0x153
#define ElmLeaveStorePlural	0x154
#define ElmLeaveDelete	0x155
#define ElmLeaveNewMailArrived	0x156
#define ElmLeaveAppendDenied	0x157
#define ElmLeaveCouldNotAppend	0x158
#define ElmLeaveTempFileDenied	0x159
#define ElmLeaveCouldNotCreate	0x15a
#define ElmLeaveCloseFailedTemp	0x15b
#define ElmLeaveProblemsSavingPerms	0x15c
#define ElmLeaveErrorOnStat	0x15d
#define ElmLeaveLinkFailed	0x15e
#define ElmLeaveCouldntModifyFolder	0x15f
#define ElmLeaveCantCopyMailbox	0x160
#define ElmLeaveSavedMailIn	0x161
#define ElmLeaveKeepingEmpty	0x162
#define ElmLeaveProblemsRestoringPerms	0x163
#define ElmLeaveChangingAccessTime	0x164
#define ElmLeaveCouldntRemoveCurLock	0x165
#define ElmLeaveErrorCreatingLock	0x166
#define ElmLeaveCantCreateLock	0x167
#define ElmLeaveWaitingToRead	0x168
#define ElmLeaveTimedOutRemoving	0x169
#define ElmLeaveThrowingAwayLock	0x16a
#define ElmLeaveGivingUp	0x16c
#define ElmLeavePleaseTryAgain	0x16d
#define ElmLeaveErrorTimedOutLock	0x16e
#define ElmLeaveErrorReopenMailbox	0x16f
#define ElmLeaveErrorFlockMailbox	0x170
#define ElmLeaveCouldntUnlockOwnMailbox	0x171
#define ElmLeaveCouldntRemoveOwnLock	0x172
#define ElmLimitEnterCriteria	0x173
#define ElmLimitAlreadyHave	0x174
#define ElmYesWord	0x175
#define ElmLimitAdding	0x176
#define ElmNoWord	0x177
#define ElmLimitChanging	0x178
#define ElmLimitNotValidCriterion	0x179
#define ElmLimitReturnToUnlimited	0x17a
#define ElmLimitMessagesSelected	0x17b
#define ElmLimitMessageSelected	0x17c
#define ElmLimitNoMessagesSelected	0x17d
#define ElmSetCurrentTo	0x17e
#define ElmTermInitFailed	0x17f
#define ElmSendTheMessageTo	0x180
#define ElmTo	0x181
#define ElmSubjectOfMessage	0x182
#define ElmSubject	0x183
#define ElmMailNotSent	0x184
#define ElmNoSubjectContinue	0x185
#define ElmMailNotSend	0x186
#define ElmCopiesTo	0x187
#define ElmTooManyPeople	0x188
#define ElmCopyMessageYN	0x189
#define ElmCouldNotCreateFile	0x18a
#define ElmCouldNotFindForm	0x18b
#define ElmCouldNotOpenReply	0x18c
#define ElmCouldNotMakeTemp	0x18d
#define ElmUsedDumpMailer	0x18e
#define ElmSendingMail	0x18f
#define ElmMailerReturnedError	0x190
#define ElmMailSent	0x191
#define ElmRecallLastInstead	0x192
#define ElmRecallLastKept	0x193
#define ElmErrorTryingToWrite	0x19a
#define ElmNoEncryptInBatch	0x19b
#define ElmWriteFailedCopyAcross	0x19c
#define ElmBounceOffRemote	0x19d
#define ElmWarningBlankIgnored	0x19e
#define ElmBackquoteCmdFailed	0x19f
#define ElmAlreadyRunning1	0x1a0
#define ElmAlreadyRunning2	0x1a1
#define ElmAlreadyRunning3	0x1a2
#define ElmSorryCantUnlinkTemp	0x1a3
#define ElmFailOnOpenNewmbox	0x1a4
#define ElmWhatsThisTempExists	0x1a5
#define ElmIGiveUp	0x1a6
#define ElmCouldntOpenForTemp	0x1a7
#define ElmCouldntReopenForTemp	0x1a8
#define ElmReadingInMessage	0x1a9
#define ElmReadingInMessage0	0x1aa
#define ElmReadingMessage0	0x1ab
#define ElmCouldntSeekEndFolder	0x1ac
#define ElmWriteToTempFailed	0x1ad
#define ElmMailBeingForwardTo	0x1ae
#define ElmFOlderCorrupt	0x1af
#define ElmCouldntAllocMemory	0x1b0
#define ElmCloseOnFolderFailed	0x1b1
#define ElmCloseOnTempFailed	0x1b2
#define ElmLengthNESpool	0x1b3
#define ElmOn	0x1b4
#define ElmOff	0x1b5
#define ElmSelectOptionLetter	0x1b6
#define ElmSaveOptions	0x1b7
#define ElmCommandUnknown	0x1b8
#define ElmOptionsEditor	0x1b9
#define ElmOptionCalendar	0x1ba
#define ElmOptionDisplay	0x1bb
#define ElmOptionEditor	0x1bc
#define ElmOptionFolder	0x1bd
#define ElmOptionSorting	0x1be
#define ElmOptionAlias	0x1bf
#define ElmOptionOutbound	0x1c0
#define ElmOptionPrint	0x1c1
#define ElmOptionYourFullname	0x1c2
#define ElmOptionArrow	0x1c3
#define ElmOptionMenu	0x1c4
#define ElmOptionUserLevel	0x1c5
#define ElmOptionNamesOnly	0x1c6
#define ElmUseSpaceToToggle	0x1c7
#define ElmSpaceToChange	0x1c8
#define ElmSpaceForNext	0x1c9
#define ElmResortingFolder	0x1ca
#define ElmSortRSentDate	0x1cb
#define ElmSortRRecvDate	0x1cc
#define ElmSortRMailbox	0x1cd
#define ElmSortRSender	0x1ce
#define ElmSortRSize	0x1cf
#define ElmSortRSubject	0x1d0
#define ElmSortRStatus	0x1d1
#define ElmSortSentDate	0x1d2
#define ElmSortRecvDate	0x1d3
#define ElmSortMailbox	0x1d4
#define ElmSortSender	0x1d5
#define ElmSortSize	0x1d6
#define ElmSortSubject	0x1d7
#define ElmSortStatus	0x1d8
#define ElmPressKeyHelp	0x1e6
#define ElmKeyPrompt	0x1e7
#define ElmKeyIsntUsed	0x1e8
#define ElmBeginningUser	0x1e9
#define ElmIntermediateUser	0x1ea
#define ElmExpertUser	0x1eb
#define ElmResortingAliases	0x1ec
#define ElmASortRAlias	0x1ed
#define ElmASortRName	0x1ee
#define ElmASortRText	0x1ef
#define ElmASortAlias	0x1f0
#define ElmASortName	0x1f1
#define ElmASortText	0x1f2
#define ElmFolderCorrupt	0x1f3
#define ElmTag	0x1f4
#define ElmTagged	0x1f5
#define ElmCapTagged	0x1f6
#define ElmDelete	0x1f7
#define ElmMarkDelete	0x1f8
#define ElmCapMarkDelete	0x1f9
#define ElmUndelete	0x1fa
#define ElmUndeleted	0x1fb
#define ElmCapUndeleted	0x1fc
#define ElmEnterPattern	0x1fd
#define ElmMessagesMatchPattern	0x1fe
#define ElmSomeMessagesATagged	0x1ff
#define ElmAMessageATagged	0x200
#define ElmRemoveTags	0x201
#define ElmRemoveTag	0x202
#define ElmTaggedMessages	0x203
#define ElmTaggedMessage	0x204
#define ElmNoMatchesNoTags	0x205
#define ElmMatchAnywhere	0x206
#define ElmMatchPattern	0x207
#define ElmMatchPatternInEntire	0x208
#define ElmSearchingFolderPattern	0x209
#define ElmMatchSeekFailed	0x20a
#define ElmCouldntMallocBytes	0x20b
#define ElmChangeToWhichFolder	0x20c
#define ElmArgsHelp1	0x217
#define ElmArgsHelp2	0x218
#define ElmAlreadyReadingThatFolder	0x21f
#define ElmCantOpenFolderReadNONL	0x220
#define ElmBatchDirNotice	0x221
#define ElmDirNotice	0x222
#define ElmDirNoticeNo	0x223
#define ElmDirNoticeYes	0x224
#define ElmDirNoticeQuit	0x225
#define ElmArgsIngoringDebug	0x226
#define ElmArgsTooManyAddresses	0x227
#define ElmArgsSubjectNotSend	0x228
#define ElmCouldNotOpenNewElmrc	0x22a
#define ElmBadSortKeyInElmrc	0x22b
#define ElmBadAliasSortInElmrc	0x22c
#define ElmSignatureObsolete	0x22d
#define ElmBouncebackGTMaxhops	0x22e
#define ElmTimeoutLTTen	0x22f
#define ElmBadLineElmrc	0x230
#define ElmBatchNoticeFoldersDir	0x231
#define ElmNoticeFoldersDir	0x232
#define ElmTooManyWeedHeaders	0x233
#define ElmTooManyWeedPmalloc	0x234
#define ElmNoMemDefaultWeed	0x235
#define ElmCannotInitErrorExpanding	0x236
#define ElmCouldntMakeTempFileName	0x237
#define ElmCouldntOpenForWriting	0x238
#define ElmSureYouWantToRemail	0x239
#define ElmBounceCancelled	0x23a
#define ElmResendingMail	0x23b
#define ElmMailResent	0x23c
#define ElmFilledInForm	0x23d
#define ElmReYourMail	0x23e
#define ElmNoEditingAllowed	0x23f
#define ElmForwardedMail	0x240
#define ElmBuildRAHitMaxHops	0x241
#define ElmNotAValidMessageNum	0x242
#define ElmCouldntSeekBytesIntoFlle	0x243
#define ElmEditOutgoingMessage	0x244
#define ElmCannotDetermineToName	0x245
#define ElmCannotSaveTo	0x246
#define ElmCannotSaveToNorSent	0x247
#define ElmCannotSaveToSavingInstead	0x248
#define ElmAppendCopyCouldntReadFile	0x249
#define ElmNoSave	0x24a
#define ElmUncondSaveByName	0x24b
#define ElmSentFolder	0x24c
#define ElmCondSaveByName	0x24d
#define ElmSaveCopyInPrompt	0x24e
#define ElmListFoldersHelp1	0x24f
#define ElmListFoldersHelp2	0x250
#define ElmShownWithSelect	0x251
#define ElmShownNoSelect	0x252
#define ElmFolderWord	0x253
#define ElmMailboxWord	0x254
#define ElmLevel0MenuLine1	0x255
#define ElmLevel0MenuLine2	0x256
#define ElmLevel0MenuLine3	0x257
#define ElmLevel1MenuLine1	0x258
#define ElmLevel1MenuLine2	0x259
#define ElmLevel1MenuLine3	0x25a
#define ElmPreparePagerPipe	0x25b
#define ElmPreparePagerFork	0x25c
#define ElmPreparePagerDup	0x25d
#define ElmPreparePagerChildFdopen	0x25e
#define ElmPreparePagerParentFdopen	0x25f
#define ElmMessageAddressedTo	0x260
#define ElmTaggedPrivate	0x261
#define ElmTaggedCompanyConfidential	0x262
#define ElmTaggedUrgent	0x263
#define ElmCommaUrgent	0x264
#define ElmAndUrgent	0x265
#define ElmMessageHasExpired	0x266
#define ElmAndHasExpired	0x267
#define ElmPrematureEndOfFile	0x268
#define ElmCommandIToReturn	0x269
#define ElmUseIToReturnIndex	0x26a
#define ElmPipe	0x26b
#define ElmSystemCall	0x26c
#define ElmScanForCalendarCmd	0x26d
#define ElmCantScanForCalendar	0x26e
#define ElmDisplayReturnAdd	0x26f
#define ElmMessageMarkedForDeleteion	0x271
#define ElmForwardMessage	0x272
#define ElmMailMessage	0x274
#define ElmPrintMessage	0x275
#define ElmMessageTagged	0x277
#define ElmMessageUntagged	0x278
#define ElmMessageUndeleted	0x279
#define ElmFolder	0x27a
#define ElmMailbox	0x27b
#define ElmCommandLine	0x27c
#define ElmIllegalInstructionSignal	0x27d
#define ElmFloatingPointSignal	0x27e
#define ElmBusErrorSignal	0x27f
#define ElmSegmentViolationSignal	0x280
#define ElmStoppedUseFGToReturn	0x281
#define ElmBackInElmRedraw	0x282
#define ElmShownNoSelectPlural	0x283
#define ElmKeyF1	0x284
#define ElmKeyF2	0x285
#define ElmKeyF3	0x286
#define ElmKey0F4	0x287
#define ElmKey0F5	0x288
#define ElmKey0F6	0x289
#define ElmKey1F4	0x28a
#define ElmKey1F5	0x28b
#define ElmKey1F6	0x28c
#define ElmKeyF7	0x28d
#define ElmKeyF8	0x28e
#define ElmKeyAF1	0x28f
#define ElmKeyAF2	0x290
#define ElmKeyAF3	0x291
#define ElmKeyAF4	0x292
#define ElmKeyAF8	0x293
#define ElmKeyYF1	0x294
#define ElmKeyYF8	0x295
#define ElmKeyRF1	0x296
#define ElmKeyRF3	0x297
#define ElmKeyRF4	0x298
#define ElmKeyRF5	0x299
#define ElmKeyRF6	0x29a
#define ElmKeyRF7	0x29b
#define ElmKeyRF8	0x29c
#define ElmKeyCF1	0x29d
#define ElmKeyCF2	0x29e
#define ElmKeyCF4	0x29f
#define ElmKeyCF5	0x2a0
#define ElmKeyCF6	0x2a1
#define ElmKeyCF8	0x2a2
#define ElmSortingMessagesBy	0x2a3
#define ElmPadRevDateMailSent	0x2a4
#define ElmAbrtRevDateMailSent	0x2a5
#define ElmLongRevDateMailSent	0x2a6
#define ElmPadRevRecv	0x2a7
#define ElmAbrRevRecv	0x2a8
#define ElmLongRevRecv	0x2a9
#define ElmPadRevMailbox	0x2aa
#define ElmAbrRevMailbox	0x2ab
#define ElmLongRevMailbox	0x2ac
#define ElmPadRevSender	0x2ad
#define ElmAbrRevSender	0x2ae
#define ElmLongRevSender	0x2af
#define ElmPadRevLines	0x2b0
#define ElmAbrRevLines	0x2b1
#define ElmLongRevLines	0x2b2
#define ElmPadRevSubject	0x2b3
#define ElmAbrRevSubject	0x2b4
#define ElmLongRevSubject	0x2b5
#define ElmPadRevStatus	0x2b6
#define ElmAbrRevStatus	0x2b7
#define ElmLongRevStatus	0x2b8
#define ElmPadMailSent	0x2b9
#define ElmAbrMailSent	0x2ba
#define ElmLongMailSent	0x2bb
#define ElmPadMailRecv	0x2bc
#define ElmAbrMailRecv	0x2bd
#define ElmLongMailRecv	0x2be
#define ElmPadMailbox	0x2bf
#define ElmAbrMailbox	0x2c0
#define ElmLongMailbox	0x2c1
#define ElmPadSender	0x2c2
#define ElmAbrSender	0x2c3
#define ElmLongSender	0x2c4
#define ElmPadLines	0x2c5
#define ElmAbrLines	0x2c6
#define ElmLongLines	0x2c7
#define ElmPadSubject	0x2c8
#define ElmAbrSubject	0x2c9
#define ElmLongSubject	0x2ca
#define ElmPadStatus	0x2cb
#define ElmAbrStatus	0x2cc
#define ElmLongStatus	0x2cd
#define ElmGetTokenOverNested	0x2ce
#define ElmUseShellName	0x2cf
#define ElmShellCommand	0x2d0
#define ElmPressAnyKeyToReturn	0x2d1
#define ElmReturnCodeWas	0x2d2
#define ElmPipeTo	0x2d3
#define ElmTooManyMessagesSelected	0x2da
#define ElmContentsOfYourFolderDir	0x2db
#define ElmFoldersWhichMatch	0x2dc
#define ElmFilesWhichMatch	0x2dd
#define ElmCopyingFromCopyingTo	0x2de
#define ElmWelcomeToNewElm	0x2df
#define ElmEmergencyExitTaken	0x2e0
#define ElmWriteFailedExitingIntact	0x2e1
#define ElmChange	0x2e2
#define ElmWindowSizeTooSmall	0x2e3
#define ElmSortUnknown	0x2e4
#define ElmEnterLastSelected	0x2e5
#define ElmEnterSelected	0x2e6
#define ElmHelpUndeletePattern	0x2e7
#define ElmNoIncludeFilename	0x2e8
#define ElmNoContentTypeGiven	0x2e9
#define ElmEncodingIsIllegal	0x2ea
#define ElmIncludeCannotAccess	0x2eb
#define ElmUnknownEncodingInInclude	0x2ec
#define ElmCantStatIncludedFile	0x2ed
#define ElmCantOpenIncludedFile	0x2ee
#define ElmPressAnyKeyIndex	0x2ef
#define ElmArgsInclFileNotSend	0x2f0
#define ElmArgsInclFileBatch	0x2f1
#define ElmOptionArrowMenu	0x2f8
#define ElmOptionArrowHelp	0x2f9
#define ElmOptionBorderMenu	0x2fa
#define ElmOptionBorderHelp	0x2fb
#define ElmOptionCalendarMenu	0x2fc
#define ElmOptionCalendarHelp	0x2fd
#define ElmOptionDisplayMenu	0x2fe
#define ElmOptionDisplayHelp	0x2ff
#define ElmOptionEditorMenu	0x300
#define ElmOptionEditorHelp	0x301
#define ElmOptionFolderMenu	0x302
#define ElmOptionFolderHelp	0x303
#define ElmOptionHoldMenu	0x304
#define ElmOptionHoldHelp	0x305
#define ElmOptionJreplyMenu	0x306
#define ElmOptionJreplyHelp	0x307
#define ElmOptionKpauseMenu	0x308
#define ElmOptionKpauseHelp	0x309
#define ElmOptionaLiasMenu	0x30a
#define ElmOptionaLiasHelp	0x30b
#define ElmOptionMenuMenu	0x30c
#define ElmOptionMenuHelp	0x30d
#define ElmOptionNameMenu	0x30e
#define ElmOptionNameHelp	0x30f
#define ElmOptionOutboundMenu	0x310
#define ElmOptionOutboundHelp	0x311
#define ElmOptionPrintMenu	0x312
#define ElmOptionPrintHelp	0x313
#define ElmOptionReplyMenu	0x314
#define ElmOptionReplyHelp	0x315
#define ElmOptionSortMenu	0x316
#define ElmOptionSortHelp	0x317
#define ElmOptionTextMenu	0x318
#define ElmOptionTextHelp	0x319
#define ElmOptionUserMenu	0x31a
#define ElmOptionUserHelp	0x31b
#define ElmOptionVisualMenu	0x31c
#define ElmOptionVisualHelp	0x31d
#define ElmOptionWantMenu	0x31e
#define ElmOptionWantHelp	0x31f
#define ElmOptionYourMenu	0x320
#define ElmOptionYourHelp	0x321
#define ElmOptionZdashMenu	0x322
#define ElmOptionZdashHelp	0x323
#define ElmIntReentrantBuiltinEditor	0x32c
#define ElmCannotCreateFolderState	0x32d
#define ElmCannotCreateEnvParam	0x32e
#define ElmCouldntSeekBytesIntoFolder	0x32f
#define ElmPrintDontKnowHow	0x330
#define ElmPrintPipeFailed	0x331
#define ElmPrintPressAKey	0x332
#define ElmPrintJobSpooled	0x333
#define ElmPrintFailCode	0x334
#define ElmPrintFailStatus	0x335
#define ElmCouldntSeekBytesIntoTempFile	0x336
#define ElmCannotExpand	0x337
#define ElmNoItemToScan	0x338
#define ElmConfirmFilesAppend	0x339
#define ElmConfirmFolderAppend	0x33a
#define ElmConfirmFilesCreate	0x33b
#define ElmConfirmFolderCreate	0x33c
#define ElmSavingToInstead	0x33d
#define ElmHelpTagAndNext	0x33e
#define ElmCouldntSeekTempEnd	0x33f
#define ElmOptionCtrlLHelp	0x340
#define ElmOptionGreaterHelp	0x341
#define ElmOptionReturnHelp	0x342
#define ElmReadMessageIncrement	0x343
#define ElmSleepMessageInvalid	0x344
#define ElmVfyPromptPleaseChoose	0x345
#define ElmVfyMenuUser0	0x346
#define ElmVfyPromptAndNow	0x347
#define ElmVfyMenuEditForm	0x348
#define ElmVfyMenuEditMake	0x349
#define ElmVfyMenuEditMsg	0x34a
#define ElmVfyMenuVfyCpy	0x34b
#define ElmVfyMenuIspell	0x34c
#define ElmVfyMenuShell	0x34d
#define ElmVfyMenuSndFgt	0x34e
#define ElmVfyMessageKept	0x34f
#define ElmVfyNoFieldsInForm	0x350
