namespace HackCompiler.Tokenizer
{
    internal class Tokenizer : ITokenizer
    {
        private readonly FileStream _fs;
        private const string _symbols = "{}()[],.;+-*/&|<>=~";
        private string _currentToken = "";

        public Tokenizer(FileStream fileStream)
        {
            _fs = fileStream;
        }

        // Reads forward until it finds a non whitespace character. If that is the start of a comment, it reads forward skipping over the comment.
        // If it is not a comment, the filestream position is reset to the position it was at before this method is called.
        // After skipping over the comment, the same function is recursively called until a non comment character is reached, as there can obviously be multiple comments one after another.
        private void SkipComments()
        {
            string buffer = "";
            long prevPos = _fs.Position;
            int c = _fs.ReadByte();

            while (char.IsWhiteSpace((char)c)) c = (char)_fs.ReadByte();

            if (c == '/')
            {
                int next = _fs.ReadByte();
                if (next == -1)
                {
                    _fs.Position = prevPos;
                    return;
                }

                // must be single line comment like this.
                if ((char)next == '/')
                {
                    while ((char)next != '\n' && next != -1) next = _fs.ReadByte();
                    SkipComments();
                }
                /*must be multi line comment like this*/
                else if ((char)next == '*')
                {
                    while (buffer.Length < 2 || buffer.Substring(buffer.Length - 2, 2) != "*/")
                    {
                        int nc = _fs.ReadByte();
                        if (nc == -1) break;
                        buffer += (char)nc;
                    }
                    SkipComments();
                }
                else _fs.Position = prevPos;
            }
            else _fs.Position = prevPos;
        }


        public void Advance()
        {
            bool nextTokenFound = false;
            bool inStringConst = false;
            string token = "";

            SkipComments();
            while (!nextTokenFound)
            {
                char c = (char)_fs.ReadByte();
                if (c == '"' || inStringConst)
                {
                    token += c;
                    // need to take into account escaped quotes i.e. \" ?

                    if (inStringConst && c == '"') nextTokenFound = true;
                    else inStringConst = true;
                }
                else if (_symbols.Any(s => s == c))
                {
                    if (c != '/') { }// todo: take comments into account!
                    nextTokenFound = true;

                    if (token != "") _fs.Position -= 1;
                    else token += c;
                }
                else if (char.IsWhiteSpace(c))
                {
                    if (token != "") nextTokenFound = true;
                }
                else token += c;
                
            }

            _currentToken = token;
        }

        public bool HasMoreTokens()
        {
            long startingPosition = _fs.Position;
            bool hasMoreTokens = false;
            SkipComments();
            int c = _fs.ReadByte();

            while (c != -1)
            {
                if (!char.IsWhiteSpace((char)c))
                {
                    hasMoreTokens = true;
                    break;
                }
                c = _fs.ReadByte();
            }

            _fs.Position = startingPosition;

            return hasMoreTokens;
        }

        public string Identifier() =>  _currentToken;

        public int IntVal() => int.Parse(_currentToken);

        public Shared.KeyWord KeyWord()
        {
            foreach (Shared.KeyWord kw in Enum.GetValues(typeof(Shared.KeyWord)))
            {
                if (String.Equals(kw.ToString(), _currentToken, StringComparison.OrdinalIgnoreCase)) return kw;
            }

            return Shared.KeyWord.FALSE; // shouldnt ever get here
        }

        public string StringVal() => _currentToken[1..^1];
        
        public char Symbol() => _currentToken[0];
        
        public Shared.TokenType TokenType()
        {
            if (_symbols.Any(s => s.ToString() == _currentToken)) return Shared.TokenType.SYMBOL;
            if (_currentToken[0] == '"') return Shared.TokenType.STRING_CONST;
            if (Enum.GetValues(typeof(Shared.KeyWord)).Cast<Shared.KeyWord>().Any(kw => string.Equals(kw.ToString(), _currentToken, StringComparison.OrdinalIgnoreCase))) return Shared.TokenType.KEYWORD;
            if (int.TryParse(_currentToken, out var _)) return Shared.TokenType.INT_CONST;
            else return Shared.TokenType.IDENTIFIER;
        }
    }
}
