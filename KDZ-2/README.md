# Второе КДЗ в курсе АиСД ВШЭ
## Автор: Кобызев Илья Сергеевич

### Описание файлов

- [main.cpp](main.cpp): основная программа, генерирует строки, измеряет время, создает таблицы
- [include](include): папка с определением используемых в `main.cpp` функций
    - [search.h](include/search.h): алгоритмы поиска
    - [utility.h](include/utility.h): вспомогательные фунции
- [tables](tables): папка с таблицами измерений. `clear` - без символов подстановки, `mod` - с ними. `small` - размер 10000, `big` - 100000
- [report](report): папка с отчетами и вспомогательными данными
    - [report.pdf](report/report.pdf): сам отчет
    - [charts.ipynb](report/ipynb/charts.ipynb): код для генерации графиков
    - [charts.tex](report/tex/charts.tex): исходный код отчета