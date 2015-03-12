# solinvictus
UI Automation, Registry, Json, MsiExec

I wrote this code to help me do some tasks that can be automated by the UI Automation API.

Q: Why UI Automation?

A: UI Automation provides the action needed when when a Yes/No button needs to be pressed or the OK/Cancel button to be clicked. With UI Automation, I can programmatically do just that.

Q:Why Registry API?

A: I needed a way to look at the registry for a specific key, name and value. Instead to eyeballing it myself I can just write the code for doing just that.

Q: Why MsiExec?

A: Calling MsiExec within the context of Automation allows me just run an install file (usually a .msi file) without me doing all the manual step.

Q: Why JsonCpp?

A: JsonCpp provided the features I needed to implement a way of storing meta-data in json format. This way, meta-data is decoupled from code.
