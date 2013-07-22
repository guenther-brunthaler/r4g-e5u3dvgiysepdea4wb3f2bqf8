# This needs the "revisiontime" script from the
# trunk-jv3gwuidf2ezyr5vbqavqtxyh branch in order to work. See the document
# locating_required_urls.txt in the top-level directory for more details.

ASCIIDOCS = $(shell find -type f -name "*.asciidoc" | sed -e 's, ,\\ ,g')
HTMLS = $(patsubst %.asciidoc,%.html,$(ASCIIDOCS))
TARGETS = $(HTMLS)

all: $(TARGETS)

.PHONY: all clean
.SUFFIXES: .asciidoc .html

.asciidoc.html:
	asciidoc -a revnumber=`revisiontime -F "$@"` -o "$@" "$<"

clean:
	-rm $(TARGETS)
