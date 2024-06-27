#include "codeblockhighlighter.h"


CodeBlockHighlighter::CodeBlockHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {}

void CodeBlockHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat codeFormat;
    codeFormat.setForeground(Qt::black);

    QRegularExpression codeBlockRegex("```cpp(.+?)```", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator i = codeBlockRegex.globalMatch(text);

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(1), match.capturedLength(1), codeFormat);
    }
}
