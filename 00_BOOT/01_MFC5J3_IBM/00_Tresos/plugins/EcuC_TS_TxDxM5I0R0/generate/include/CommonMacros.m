[!/* --------{ EB Automotive C Source File }-------------------------------------- */!]
[!NOCODE!]

[!MACRO "GuardedDefine", "Name", "Params"="''", "Comment"="''", "Indent"="''"!][!//
[!"$Indent"!]#ifdef [!"$Name"!]
[!"$Indent"!]  #error already defined: [!"$Name"!]
[!"$Indent"!]#endif
[!"$Indent"!]/** \brief [!"$Comment"!] */
[!"$Indent"!]#define [!"$Name"!][!"$Params"!][!WS!][!//
[!ENDMACRO!]

[!ENDNOCODE!][!//
