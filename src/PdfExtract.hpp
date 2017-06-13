#ifndef PDFEXTRACT_HPP
#define PDFEXTRACT_HPP

#include <QMap>
#include <QHash>
#include <QString>
typedef QMap<int, QString> TextData;

class PdfExtract
{
public:
    PdfExtract();
    void addText(int page, int x, int y, const QString& text);
    void clear();
    QString pageText(int page) const;

private:
    QHash<int, QMap<int, TextData > > _pagesRaw;
};

#endif // PDFEXTRACT_HPP
