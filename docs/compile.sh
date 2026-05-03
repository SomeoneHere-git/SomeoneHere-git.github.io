#/bin/bash

#Delete old files
rm ./*.png
rm ./*.pdf

for file in ./markdown/*.puml; do
  plantuml "$file"
done

for file in ./markdown/*.typ; do
  typst compile "$file"
done
