#include "PdfExtract.hpp"

#include <QDebug>

PdfExtract::PdfExtract()
{

}

void PdfExtract::addText(int page, int x, int y, const QString &text)
{
    if (text.length()) {
        //qDebug() << "add:" << text << x << y;
        int key = keyNear(_pages[page][y], x, 60);
        if (key != x) {
            _pages[page][y][key] += " " + text;
        }
        else {
            _pages[page][y][key] += text;
        }
    }
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

TextTable PdfExtract::findTable(const QString &columnName, const QString& columnHead)
{
    //qDebug() << _pages[36];
    foreach(int pageKey,  _pages.keys()) {
        TextPage page = _pages[pageKey];
        foreach(int y, page.keys()) {
            TextRow row = page[y];
            foreach(int x, row.keys()) {
                QString col = row[x];
                if (col.contains(columnName, Qt::CaseInsensitive)) {
                    //qDebug() << "p." << pageKey << x << "," << y << colNear(row, x, 250);
                    foreach(int yy,  page.keys()) {
                        TextRow searchRow = page[yy];
                        //qDebug() << yy << searchRow;
                        //qDebug() << isNear(searchRow, x, 250);
                        TextRow result = colNear(searchRow, x, 500);
                        if (!result.empty()) {
                            if (result.first().contains(columnHead, Qt::CaseInsensitive)) {
                                qDebug() << "p." << pageKey << columnName << columnHead
                                         << valueNear(page, result.keys().first(), y, 40, 5).replace(" ", "");
                            }
                        }
                    }
                    //return TextTable();
                }
            }
        }
    }

    return TextTable();
}

void PdfExtract::parsePage(const TextPage &page)
{

}

TextRow PdfExtract::colNear(TextRow row, int nearX, int dx)
{
    TextRow ret;

    foreach(int x, row.keys()) {
        if (x > nearX - dx && x < nearX + dx) {
            ret[x] = row[x];
        }
    }
    return ret;
}

int PdfExtract::keyNear(TextRow row, int nearX, int dx)
{
    foreach(int x, row.keys()) {
        if (x > nearX - dx && x < nearX + dx) {
            return x;
        }
    }
    return nearX;
}

QString PdfExtract::valueNear(TextPage page, int nearX, int nearY, int dx, int dy)
{
    foreach(int y, page.keys()) {
        TextRow row = page[y];
        foreach(int x, row.keys()) {
            if (x > nearX - dx && x < nearX + dx) {
                if (y > nearY - dy && y < nearY + dy) {
                    return row[x];
                }
            }
        }
    }
    return "";
}
