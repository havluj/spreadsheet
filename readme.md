# CLI spreadsheet editor
I implemented this project as a semester project for [Programming and Algorithms](https://edux.fit.cvut.cz/courses/BI-PA2/en/start) class I have taken.

It is a simple CLI spreadsheet editor that lets you do basic computation within each cell, as well as reference other cells. You can use any valid mathematical expression (+, -, /, \*, ^, %) and these functions: sum, avg, sin, cos, tan, ln, log, sqrt, pow, exp.

You can see more on the screenshots located in the screenshots folder.

## Disclaimer
The program is not properly tested nor is a best example of my coding skills. It needed to be written rapidly due to the conditions of the classes at school. Please, be aware that I had to respect certain guidelines and boundaries because this was a school project.

## How to compile & run
- `make all` (or `make compile` and `make doc`) to compile and build the documentation
- `make clean` to clean the project folder
- `./spreadsheet`

## Original assignment (in Czech)
Jednoduchý spreadsheet editor vytvořený pomocí ncurses. Do buňek je možné zadávat jednoduché výrazy (jako v kalkulačce). Editor detekuje cykly a nepovolí vytvoření výrazu, který by cyklus způsbil. Pokud je mi známo, tak parsování závorek byla jako ukázka na prosemináři, tedy zkuste naprogramovat spreadsheet tak aby bylo možné zpracovat výrazy typu: ((A1+5)/B5)-A5. Jednodušší verze je udělat výrazy bez závorek (např. A1+5/B5-A5), ovšem potom s funkcemi aplikovatelnými na sloupce/řádky typu SIN, AVG, SUM, apod.

Tento text má rámcově vymezit téma semestrální práce. Podrobnější podmínky viz. Edux.
