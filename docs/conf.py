DOXYFILE = 'Doxyfile-mcss'

SHOW_UNDOCUMENTED = True

STYLESHEETS = [
    'https://fonts.googleapis.com/css?family=Source+Sans+Pro:400,400i,600,600i%7CSource+Code+Pro:400,400i,600',
    '../css/m-dark+documentation.compiled.css',
    'custom.css'
]

LINKS_NAVBAR1 = [
    (None, "getting-started", []),
    (None, "api", [])
]

LINKS_NAVBAR2 = [
    (
        '<a href="#">Other</a>',
        [
            (None, "pages"),
            (None, "annotated"),
            (None, "namespaces"),
            (None, "files"),
        ],
    ),
]
