# we step into src because qmake is b0rked
cd src
qmake -recursive -tp vc moose.pro

AFTER='
Project("{2150E333-8FDC-42A3-9474-1A3956D46DE8}") = "Solution Items", "Solution Items", "{780C13D3-8172-4EE0-8FD5-26ED6489851C}"
	ProjectSection(SolutionItems) = preProject
		include.pro = include.pro
	EndProjectSection
EndProject'

echo "$AFTER" >> moose.sln