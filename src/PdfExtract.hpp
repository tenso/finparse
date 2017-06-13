#ifndef PDFEXTRACT_HPP
#define PDFEXTRACT_HPP

#include <QMap>
#include <QString>
#include <QVector>

typedef QMap<int, QString> TextRow;
typedef QMap<int, TextRow > TextPage;
typedef QVector<QVector<QString> > TextTable;

class PdfExtract
{
public:
    PdfExtract();
    void addText(int page, int x, int y, const QString& text);
    void clear();
    QString pageText(int page) const;
    //Look for a table that has the ordered items in 'columnOne' in the first column
    //skipping unmatched items in the process
    TextTable findTable(const QString &columnName, const QString& columnHead);
    void parsePage(const TextPage& page);

    TextRow colNear(TextRow row, int nearX, int dx);
    int keyNear(TextRow row, int nearX, int dx);

    QString valueNear(TextPage page, int nearX, int nearY, int dx, int dy);

private:
    QMap<int, TextPage> _pages;
};

#endif // PDFEXTRACT_HPP
