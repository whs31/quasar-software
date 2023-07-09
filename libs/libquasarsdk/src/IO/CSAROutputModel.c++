#include "CSAROutputModel.h"
#include <QtCore/QTextCodec>

namespace QuasarSDK::IO
{

  SAROutputModel::SAROutputModel(QObject* parent)
    : MessageModel(parent)
    , m_state(State::Text)
    , m_formatValue(0)
    , m_cursorPosition({0, 0})
  {}

  void SAROutputModel::newline() noexcept
  {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_storage.emplace_back(std::move(make_unique<SARMessage>()));
    endInsertRows();
  }

  void SAROutputModel::print(const QByteArray& data) noexcept
  {
    QString text;

    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QTextCodec* textCodec = QTextCodec::codecForName("UTF-8");
    QString dataString = textCodec->toUnicode(data);
    #else
    QString dataString = QStringDecoder(QStringDecoder::Utf8)(data);
    #endif

    QString::const_iterator it = dataString.cbegin();
    while(it != dataString.cend())
    {
      QChar c = *it;
      switch(m_state)
      {
        case State::Text:
          if (c.toLatin1() == 0x1B)
          {
            this->appendString(text);
            text.clear();
            m_state = State::Escape;
          }
          else if (c == '\n')
          {
            this->appendString(text);
            text.clear();
            this->newline();

            m_cursorPosition.x = 0;
            m_cursorPosition.y++;
          }
          else if (c == '\t')
          {
            for(int i = 0; i < 4 - (text.size() % 4); i++)
              text.append(' ');
          }
          else if (c.isPrint())
            text.append(c);
          break;

        case State::Escape:
          m_formatValue = 0;
          if (c == '[')
            m_state = State::Format;
          else if (c == '(')
            m_state = State::ResetFont;
          break;

        case State::Format:
          if (c >= '0' && c <= '9')
            m_formatValue = m_formatValue * 10 + (c.cell() - '0');
          else
          {
            if (c == ';' || c == 'm')  // Format
            {
              if (m_formatValue == 0)  // reset format
              {
//                                _curentFormat = _format;
              }
              else if (m_formatValue == 4)  // underline
              {
//                                _curentFormat.font().setUnderline(true);
              }
              else if (m_formatValue == 7)  // reverse
              {
//                                QColor foreground = _curentFormat.foreground();
//                                _curentFormat.setForeground(_curentFormat.background());
//                                _curentFormat.setBackground(foreground);
              }
              else if (m_formatValue / 10 == 3)  // foreground
              {
//                                _curentFormat.setForeground(vt100color(static_cast<char>(_formatValue % 10) + '0'));
              }
              else if (m_formatValue / 10 == 4)  // background
              {
//                                _curentFormat.setBackground(vt100color(static_cast<char>(_formatValue % 10) + '0'));
              }

              if (c == ';')
              {
                m_formatValue = 0;
                m_state = State::Format;
              }
              else
              {
                m_state = State::Text;
              }
            }
            else if (c >= 'A' || c <= 'D')  // Cursor command
            {
              switch (c.toLatin1())
              {
                case 'A':  // up
                  // TODO
                  break;

                case 'B':  // down
                  // TODO
                  break;

                case 'C':  // right
                  m_cursorPosition.x += m_formatValue;
                  break;

                case 'D':  // left
                  m_cursorPosition.x = (qMax(m_cursorPosition.x - m_formatValue, 0));
                  break;

                default:
                  break;
              }
              m_state = State::Text;
            }
            else
            {
              m_state = State::Text;
            }
          }
          break;

        case State::ResetFont:
//                    _curentFormat = _format;
          m_state = State::Text;
          break;
      }
      it++;
    }

    this->appendString(text);
  }

  QString SAROutputModel::lastLine() const noexcept
  {
    if(m_storage.empty())
      return {};
    return m_storage.back()->message();
  }

  void SAROutputModel::setLastLine(const QString& str)
  {
    if(m_storage.empty())
      return;

    m_storage[m_storage.size() - 1]->setMessage(str);
    emit dataChanged(createIndex(rowCount() - 1, 0), createIndex(rowCount() - 1, 0));
  }

  void SAROutputModel::appendString(const QString& text)
  {
    auto str = lastLine();
    if(m_cursorPosition.x >= str.size())
      m_cursorPosition.x++;

    int removeCount = (m_cursorPosition.x + text.size()) > str.size() ? str.size()
                                                                        - m_cursorPosition.x : m_cursorPosition.x + text.size();
    str.remove(m_cursorPosition.x, removeCount * 2);
    str.insert(m_cursorPosition.x, text);

    if(m_storage.empty() and removeCount != 6)
      this->append(std::move(make_unique<SARMessage>(str, IMessage::Debug)));
    else
      this->setLastLine(str);
  }
} // QuasarSDK::IO