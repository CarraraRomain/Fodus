import libxml2
import libxslt
# TODO Config file
# TODO Header template
# TODO Header decorator
# TODO Directory handling

print("=== PyDia2Code Header only generator === ")
print("By Timothe PEREZ | 3IS 2015 @ ENSEA | www.ensea.fr")

print("Step 1 : extracting data from DIA file (Non Gzipped!)")
try:
    styledoc = libxml2.parseFile("dia-uml.xsl")
    style = libxslt.parseStylesheetDoc(styledoc)
    doc = libxml2.parseFile("engine.dia")
    result = style.applyStylesheet(doc, None)
    style.saveResultToFilename("engine.xml", result, 0)
    print("Dia2XML OK")
except:
    print("Fail at Dial2XML")
    print("Is the dia file NOT gzipped?")

style.freeStylesheet()
doc.freeDoc()
result.freeDoc()

print("Step 2 : creating headers files from XML")
try:
    styledoc = libxml2.parseFile("dia-uml2cpp.xsl")
    style = libxslt.parseStylesheetDoc(styledoc)
    doc = libxml2.parseFile("engine.xml")
    result = style.applyStylesheet(doc, None)
    style.saveResultToFilename("engine", result, 0)
    print("XML2CPP OK")
except:
    print("Fail at XML2CPP")

print("Warning, XLST lib can fail even if no exception is thrown.")
print("Make sure your headers are correctly generated")
