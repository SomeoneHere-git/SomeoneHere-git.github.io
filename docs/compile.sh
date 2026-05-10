#/bin/bash

#Delete old files
# rm ./*.png
# rm ./*.pdf

for file in ./markdown/*.puml; do
  plantuml "$file" -o "."
done

for file in ./markdown/*.typ; do
  filename=$(basename "${file%.*}.pdf")
  typst compile "$file" "./$filename"
done
