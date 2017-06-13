#include "PdfExtract.hpp"

PdfExtract::PdfExtract()
{

}

void PdfExtract::addText(int page, int x, int y, const QString &text)
{
    _pages[page][y][x] += text;
}

void PdfExtract::clear()
{
    _pages.clear();
}

QString PdfExtract::pageText(int page) const
{
    QString pageText;
    foreach(TextRow row, _pages[page]) {
        foreach(QString col, row) {
            pageText += col + " ";
        }
         pageText += "\n";
    }
    return pageText;
}

TextTable PdfExtract::findTable(const QStringList &columnOne)
{

}
