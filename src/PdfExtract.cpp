#include "PdfExtract.hpp"

PdfExtract::PdfExtract()
{

}

void PdfExtract::addText(int page, int x, int y, const QString &text)
{
    _pagesRaw[page][y][x] += text;
}

void PdfExtract::clear()
{
    _pagesRaw.clear();
}

QString PdfExtract::pageText(int page) const
{
    QString pageText;
    QMap<int, TextData > pageRows = _pagesRaw[page];
    foreach(TextData row, pageRows) {
        foreach(QString col, row) {
            pageText += col + " ";
        }
         pageText += "\n";
    }
    return pageText;
}
