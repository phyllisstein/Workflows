tell application "Finder"
	set theSelection to (get selection)
	if length of theSelection is greater than 0 then
		set pathList to {}
		repeat with anItem in theSelection
			set itemPath to quoted form of POSIX path of (anItem as text)
			set pathList to pathList & " " & itemPath
		end repeat
	else
		set pathList to (quoted form of POSIX path of (folder of the front window as alias))
	end if
	
	return pathList
end tell