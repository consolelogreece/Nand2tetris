using HackCompiler.Shared;
using HackCompiler.Tokenizer;

namespace HackCompiler.CompilationEngine
{
    // Todo: Currently do not check whether an identifier is one that exists (i.e. if a valid variable/subroutine name etc).
    internal class CompilationEngine : ICompilationEngine
    {
        private readonly List<string> _errors = new();
        private readonly ITokenizer _input;
        private readonly StreamWriter _output;
        private readonly string _ops = "+-*/&|<>=";
        private readonly string _unaryOps = "-~";
        private readonly KeyWord[] _typeKeywords = [KeyWord.INT, KeyWord.CHAR, KeyWord.BOOLEAN];
        private readonly KeyWord[] _statementKeywords = [KeyWord.LET, KeyWord.IF, KeyWord.WHILE, KeyWord.DO, KeyWord.RETURN];
        private readonly KeyWord[] _keywordConstants = [KeyWord.TRUE, KeyWord.FALSE, KeyWord.NULL, KeyWord.THIS];
        private readonly KeyWord[] _classVariableDeclarationKeywords = [KeyWord.FIELD, KeyWord.STATIC];
        private readonly KeyWord[] _subroutineKeywords = [KeyWord.CONSTRUCTOR, KeyWord.METHOD, KeyWord.FUNCTION];
        public CompilationEngine(ITokenizer input, FileStream output)
        {
            _input = input;
            _output = new StreamWriter(output);
        }
        private void LogError(string error) => _errors.Add(error);
        private void WriteOpenTag(string tag, bool newline = true) => _output.Write("<" + tag + ">" + (newline ? "\n" : ""));
        private void WriteCloseTag(string tag, bool newline = true) => _output.Write("</" + tag + ">" + (newline ? "\n" : ""));
        private static string MakeXMLSafe(string s) => s.Replace("&", "&amp;").Replace("<", "&lt;").Replace(">", "&gt;");
        private void WriteTerminal(string tag, object value)
        {
            ArgumentNullException.ThrowIfNull(value);

            WriteOpenTag(tag, false);
            _output.Write(MakeXMLSafe(value.ToString()));
            WriteCloseTag(tag, true);
        }

        private void Advance()
        {
            if (_input.HasMoreTokens()) _input.Advance();
            else throw new Exception("Unexpected EOF");
        }
        private string FormattedKeyword() => _input.KeyWord().ToString().ToLower();
        private char FormattedSymbol() => _input.Symbol();
        private string FormattedIdentifier() => _input.Identifier();
        private bool IsTokenValid(TokenType t) => _input.TokenType() == t;
        bool IsKeywordType() => IsTokenValid(TokenType.KEYWORD);
        private bool IsKeyword(KeyWord k) => IsKeywordType() && _input.KeyWord() == k;
        bool IsSymbolType() => IsTokenValid(TokenType.SYMBOL);
        bool IsSymbol(char sym) => IsSymbolType() && FormattedSymbol() == sym;
        bool IsIdentifier() => IsTokenValid(TokenType.IDENTIFIER);
        private bool IsType() => _typeKeywords.Any(IsKeyword);
  
        public void CompileClass()
        {
            try
            {
                DoCompileClass();
            }
            catch (Exception ex) {
                LogError(ex.Message);
                _output.Close();
                return;
            }

            foreach(string s in _errors)
            {
                Console.WriteLine(s);
            }
            _output.Close();
        }

        private void DoCompileClass()
        {
            WriteOpenTag("class");
            Advance();
            if (IsKeyword(KeyWord.CLASS)) WriteTerminal("keyword", "class");
            else LogError("Expected: 'Class'");

            Advance();
            if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
            else LogError("Expected: Identifier");

            Advance();
            if (IsSymbol('{')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '{'");

            Advance();

            while (_classVariableDeclarationKeywords.Any(IsKeyword)) CompileClassVarDec();
            
            while(_subroutineKeywords.Any(IsKeyword)) CompileSubroutineDec();
            
            if (IsSymbol('}')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '}'");
           
            WriteCloseTag("class");
        }

        private void CompileClassVarDec()
        {
            WriteOpenTag("classVarDec");
            WriteTerminal("keyword", FormattedKeyword());

            Advance();
            if (IsType()) WriteTerminal("keyword", FormattedKeyword());
            else if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
            else LogError("Expected: Data type.");

            Advance();
            if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
            else LogError("Expected: Identifier.");

            Advance();
            while (IsSymbol(','))
            {
                WriteTerminal("symbol", FormattedSymbol());

                Advance();
                if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
                else LogError("Expected: Identifier");

                Advance();
            }

            if (IsSymbol(';')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: ';'");

            Advance();
            WriteCloseTag("classVarDec");
        }

        private void CompileParameterList()
        {
            WriteOpenTag("parameterList");
            if (IsType()) WriteTerminal("keyword", FormattedKeyword());
            else
            {
                WriteCloseTag("parameterList");
                return;
            };

            Advance();
            if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
            else LogError("Expected: Parameter name.");

            Advance();

            while (IsSymbol(','))
            {
                WriteTerminal("symbol", FormattedSymbol());

                Advance();
                if (IsType()) WriteTerminal("keyword", FormattedKeyword());
                else LogError("Expected: Paramater type.");

                Advance();
                if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
                else LogError("Expected: Parameter name.");

                Advance();
            }

            WriteCloseTag("parameterList");
        }

        private void CompileSubroutineDec()
        {
            WriteOpenTag("subroutineDec");
            WriteTerminal("keyword", FormattedKeyword());

            Advance();
            if (IsType() || IsKeyword(KeyWord.VOID)) WriteTerminal("keyword", FormattedKeyword());
            else if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
            else LogError("Expected: Return type.");

            Advance();
            if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
            else LogError("Expected: Subroutine name.");

            Advance();
            if (IsSymbol('(')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '('");

            Advance();
            CompileParameterList();

            if (IsSymbol(')')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: ')'");

            Advance();
            CompileSubroutineBody();
            WriteCloseTag("subroutineDec");
        }

        private void CompileSubroutineBody()
        {
            WriteOpenTag("subroutineBody");
            if (IsSymbol('{')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '{'");

            Advance();
            while (IsKeyword(KeyWord.VAR)) CompileVarDec();

            CompileStatements();

            if (IsSymbol('}')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '}'");

            Advance();
            WriteCloseTag("subroutineBody");
        }

        private void CompileExpression()
        {
            WriteOpenTag("expression");
            CompileTerm();

            while (_ops.Any(IsSymbol))
            {
                WriteTerminal("symbol", FormattedSymbol());
                Advance();

                CompileTerm();
            }

            WriteCloseTag("expression");
        }

        private void CompileExpressionList()
        {
            WriteOpenTag("expressionList");
            while (!IsSymbol(')'))
            {
                CompileExpression();

                if (!IsSymbol(')'))
                {
                    if (IsSymbol(',')) WriteTerminal("symbol", FormattedSymbol());
                    else LogError("Expected: ','");

                    Advance();
                }
            }
            WriteCloseTag("expressionList");
        }

        private void CompileVarDec()
        {
            WriteOpenTag("varDec");
            WriteTerminal("keyword", FormattedKeyword());

            Advance();
            if (IsType()) WriteTerminal("keyword", FormattedKeyword());
            else if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
            else LogError("Expected: Data type.");

            Advance();
            if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
            else LogError("Expected: Variable name.");

            Advance();

            while (IsSymbol(','))
            {
                WriteTerminal("symbol", FormattedSymbol());

                Advance();
                if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
                else LogError("Expected: Variable name.");

                Advance();
            }

            if (IsSymbol(';')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: ';'");

            Advance();
            WriteCloseTag("varDec");
        }

        private void CompileTerm()
        {
            WriteOpenTag("term");
            if (IsTokenValid(TokenType.STRING_CONST))
            {
                WriteTerminal("stringConstant", _input.StringVal());
                Advance();
            }
            else if (IsTokenValid(TokenType.INT_CONST))
            {
                WriteTerminal("integerConstant", _input.IntVal());
                Advance();
            }
            else if (_keywordConstants.Any(IsKeyword))
            {
                WriteTerminal("keyword", FormattedKeyword());
                Advance();
            }
            else if (IsIdentifier())
            {
                WriteTerminal("identifier", FormattedIdentifier());
                Advance();

                if (IsSymbol('['))
                {
                    WriteTerminal("symbol", FormattedSymbol());

                    Advance();
                    CompileExpression();

                    if (IsSymbol(']')) WriteTerminal("symbol", FormattedSymbol());
                    else LogError("Expected ']'");

                    Advance();
                }
                else if (IsSymbol('.') || IsSymbol('('))
                {
                    bool isObjectMethodInvoke = IsSymbol('.');
                    WriteTerminal("symbol", FormattedSymbol());

                    Advance();
                    if (isObjectMethodInvoke)
                    {
                        if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
                        else LogError("Expected: class or variable name");
                        Advance();
                    }

                    if (IsSymbol('(')) WriteTerminal("symbol", FormattedSymbol());
                    else LogError("Expected: '('");

                    Advance();
                    CompileExpressionList();

                    if (IsSymbol(')')) WriteTerminal("symbol", FormattedSymbol());
                    else LogError("Expected: ')'");

                    Advance();
                }
            }
            else if (IsSymbol('('))
            {
                WriteTerminal("symbol", FormattedSymbol());

                Advance();
                CompileExpression();

                if (IsSymbol(')')) WriteTerminal("symbol", FormattedSymbol());
                else LogError("Expected: ')'");

                Advance();
            }
            else if (IsTokenValid(TokenType.SYMBOL) && _unaryOps.Any(IsSymbol))
            {
                WriteTerminal("symbol", FormattedSymbol());

                Advance();
                CompileTerm();
            }

            WriteCloseTag("term");
        }

        private void CompileStatements()
        {
            WriteOpenTag("statements");
            while (_statementKeywords.Any(IsKeyword))
            {
                switch (_input.KeyWord())
                {
                    case KeyWord.LET:
                        CompileLet();
                        break;
                    case KeyWord.IF:
                        CompileIf();
                        break;
                    case KeyWord.WHILE:
                        CompileWhile();
                        break;
                    case KeyWord.DO:
                        CompileDo();
                        break;
                    case KeyWord.RETURN:
                        CompileReturn();
                        break;
                }
            }

            WriteCloseTag("statements");
        }

        private void CompileDo()
        {
            WriteOpenTag("doStatement");
            WriteTerminal("keyword", "do");

            Advance();
            if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
            else LogError("Expected: Identifier");

            Advance();
            if (IsSymbol('.'))
            {
                WriteTerminal("symbol", FormattedSymbol());

                Advance();
                if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
                else LogError("Expected: Identifier");

                Advance();
            }

            if (IsSymbol('(')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '('");

            Advance();
            CompileExpressionList();
            
            if (IsSymbol(')')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: ')'");

            Advance();
            if (IsSymbol(';')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: ';'");

            Advance();
            WriteCloseTag("doStatement");
        }

        private void CompileIf()
        {
            WriteOpenTag("ifStatement");
            WriteTerminal("keyword", "if");

            Advance();
            if (IsSymbol('(')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '('");

            Advance();
            CompileExpression();

            if (IsSymbol(')')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: ')'");

            Advance();
            if (IsSymbol('{')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '{'");

            Advance();
            CompileStatements();

            if(IsSymbol('}')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '}'");

            Advance();

            if (IsKeyword(KeyWord.ELSE))
            {
                WriteTerminal("keyword", "else");

                Advance();
                if (IsSymbol('{')) WriteTerminal("symbol", FormattedSymbol());
                else LogError("Expected: '{'");

                Advance();
                CompileStatements();

                if (IsSymbol('}')) WriteTerminal("symbol", FormattedSymbol());
                else LogError("Expected: '}'");

                Advance();
            }

            WriteCloseTag("ifStatement");
        }

        private void CompileLet()
        {
            WriteOpenTag("letStatement");
            WriteTerminal("keyword", "let");

            Advance();
            if (IsIdentifier()) WriteTerminal("identifier", FormattedIdentifier());
            else LogError("Expected: Variable name.");

            Advance();
            if (IsSymbol('['))
            {
                WriteTerminal("symbol", FormattedSymbol());

                Advance();
                CompileExpression();

                if (IsSymbol(']')) WriteTerminal("symbol", FormattedSymbol());
                else LogError("Expected: ']'");

                Advance();
            }

            if (IsSymbol('=')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '='");

            Advance();
            CompileExpression();

            if (IsSymbol(';')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: ';'");

            Advance();
            WriteCloseTag("letStatement");
        }

        private void CompileReturn()
        {
            WriteOpenTag("returnStatement");
            WriteTerminal("keyword", "return");

            Advance();
            if (!IsSymbol(';')) CompileExpression();
            
            if (IsSymbol(';')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: ';'");

            Advance();

            WriteCloseTag("returnStatement");
        }

        private void CompileWhile()
        {
            WriteOpenTag("whileStatement");
            WriteTerminal("keyword", "while");

            Advance();
            if (IsSymbol('(')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '('");

            Advance();
            CompileExpression();

            if (IsSymbol(')')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: ')'");

            Advance();
            if (IsSymbol('{')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '{'");

            Advance();
            CompileStatements();

            if (IsSymbol('}')) WriteTerminal("symbol", FormattedSymbol());
            else LogError("Expected: '}'");

            Advance();
            WriteCloseTag("whileStatement");
        }

        ~CompilationEngine()
        {
            _output.Close();
        }
    }
}