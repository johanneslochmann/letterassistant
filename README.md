# letterassistant
A simple application to replace keywords in plain text files to generate documents from templates.
Keywords and their possible values are embedded in plain text files and replaced in the output.


%%%ChooseOne:OneOf:First|Second|Third
%%%ChooseAny:AnyOf:First|Second|Third|Fourth
%%%EnterShortText:ShortText:Default Value
%%%EnterLongText:LongText:Default Value
%%%EnterDate:DateEdit:

Keywords are enclosed in '!' where they are supposed to be replaced:

If ChooseOne is the keyword, !ChooseOne! is the placeholder where it is to be replaced.

The output date format can be configured via:
%%% DateFormat:dd/MM/yyyy

The number of columns in radio button groups, i.e. OneOf, can be configured via:
%%% ColumnsInRadioButtonGroups:5

The number of columns in check box button groups, i.e. AnyOf, can be configured via:
%%% ColumnsInCheckBoxButtonGroups:5
