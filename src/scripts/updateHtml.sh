#!/bin/sh

targetFile="/var/www/index.html"
updateFile="/var/www/htmlUpdate"

cat ${updateFile} | xargs -Iq sed -i 's/###/<p>q<\/p>\n###/g' ${targetFile}
sed -i 's/###//g' ${targetFile}
