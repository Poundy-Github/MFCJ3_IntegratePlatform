[!/**EB_Automotive_Template_File */!][!//
[!/*
*** multiple inclusion protection ***
*/!][!IF "not(var:defined('CANTRCV_1_T03_MACROS_M'))"!]
[!VAR "CANTRCV_1_T03_MACROS_M"="'true'"!][!/*

--------------------------------------------------------------------------
    Set the values of useful variables
--------------------------------------------------------------------------
*/!][!SELECT "as:modconf('CanTrcv')[(CommonPublishedInformation/VendorId = 1) and (CommonPublishedInformation/VendorApiInfix = 'T03')]"!][!/*

*/!][!VAR "VarChannelNumber" = "num:integer(count(CanTrcvConfigSet/*[1]/CanTrcvChannel/*))"!][!/*

* Find the job associated to a Sequence reference *
*/!][!MACRO "FindChannelSpi", "SpiSeq"!][!/*
  */!][!IF "count(node:ref($SpiSeq)/SpiJobAssignment/*) > 1"!][!/*
    */!][!ERROR!]Too many jobs for the spi sequence [!"node:name(node:ref($SpiSeq))"!]. Only one shall be defined![!ENDERROR!][!/*
  */!][!ENDIF!][!/*
  */!][!SELECT "node:ref(node:ref($SpiSeq)/SpiJobAssignment/*[1])"!][!/*
    */!][!IF "count(SpiChannelList/*) > 1"!][!/*
      */!][!ERROR!]Too many channels for this spi job [!"@name"!]. Only one shall be defined![!ENDERROR!][!/*
    */!][!ENDIF!][!/*
    */!][!VAR "spiChannelId" = "num:i(node:value(node:ref(./SpiChannelList/*[1]/SpiChannelAssignment)/SpiChannelId))"!][!/*
    */!][!IF "not(text:uniq(node:ref(./SpiChannelList/*[1]/SpiChannelAssignment)/../*/SpiChannelId, string($spiChannelId)))"!][!/*
      */!][!ERROR!]The 'SpiChannelId' = [!"SpiChannelId"!] is defined more than once![!ENDERROR!][!/*
    */!][!ENDIF!][!/*
    */!][!"$spiChannelId "!][!/*
  */!][!ENDSELECT!][!/*
*/!][!ENDMACRO!][!/*

* Find the sequence Id from a Sequence reference **
*/!][!MACRO "FindSequenceSpiId", "SpiSeq"!][!/*
*/!][!VAR "seqId" = "num:i(node:value(node:ref($SpiSeq)/SpiSequenceId))"!][!/*
  */!][!IF "not(text:uniq(node:ref($SpiSeq)/../*/SpiSequenceId, string($seqId)))"!][!/*
    */!][!ERROR!]The 'SpiSequenceId' = [!"$seqId"!] is defined more than once![!ENDERROR!][!/*
  */!][!ENDIF!][!/*
*/!][!"$seqId"!][!/*
*/!][!ENDMACRO!][!/*

* Find the wakeupSourceId Id from a wakeupsource reference *
*/!][!MACRO "FindEcuMWakeupSourceId", "EcuMWakeupSourceName"!][!/*
    */!][!LOOP "as:modconf('EcuM')[1]/EcuMConfiguration/*[1]/EcuMCommonConfiguration/EcuMWakeupSource/*[name(.) = $EcuMWakeupSourceName]"!][!/*
        */!][!"EcuMWakeupSourceId"!][!/*
        */!][!VAR "tmpEcuMWakeupSourceId" = "EcuMWakeupSourceId"!][!/*
        */!][!/* Check the unicity of the EcuMWakeupSourceName */!][!/*
        */!][!IF "count(as:modconf('EcuM')[1]/EcuMConfiguration/*[1]/EcuMCommonConfiguration/EcuMWakeupSource/*[EcuMWakeupSourceId = $tmpEcuMWakeupSourceId]) > 1"!][!/*
            */!][!ERROR!]The 'EcuMWakeupSourceId' = [!"EcuMWakeupSourceId"!] is defined more than once![!ENDERROR!][!/*
        */!][!ENDIF!][!/*
    */!][!ENDLOOP!][!/*
*/!][!ENDMACRO!][!/*

*/!][!ENDSELECT!][!/*
*** End of file ***
*/!][!ENDIF!][!//
