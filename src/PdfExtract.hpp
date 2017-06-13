#ifndef PDFEXTRACT_HPP
#define PDFEXTRACT_HPP

#include <QMap>
#include <QHash>
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
    TextTable findTable(const QStringList& columnOne);

private:
    QHash<int, TextPage> _pages;
};

#endif // PDFEXTRACT_HPP
