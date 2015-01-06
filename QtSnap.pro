TEMPLATE=subdirs
SUBDIRS = lib app
lib.subdir = QtSnap-Library
app.subdir = QtSnap-DemoApp
app.depend = lib
