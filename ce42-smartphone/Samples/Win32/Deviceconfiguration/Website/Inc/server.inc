<%
Function GetUser ()

	Dim DomainUser

	DomainUser = Request.ServerVariables ("LOGON_USER") 

	If InStr( DomainUser, "\" ) = 0 Then
		GetUser = DomainUser
	Else
		GetUser = LCase(Mid( DomainUser, InStr(DomainUser,"\")+1 ))
	End If

End Function
%>
