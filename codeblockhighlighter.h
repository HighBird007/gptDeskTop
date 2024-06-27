#ifndef CODEBLOCKHIGHLIGHTER_H
#define CODEBLOCKHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class CodeBlockHighlighter : public QSyntaxHighlighter
{
public:
    CodeBlockHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;
};

#endif // CODEBLOCKHIGHLIGHTER_H
