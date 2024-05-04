#!/bin/sh

targetFile="/var/www/index.html"
backupFile="/var/www/index.html_bak"

cp ${backupFile} ${targetFile}
