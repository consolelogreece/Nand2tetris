
using HackCompiler.Shared;

namespace HackCompiler.Tokenizer
{
    internal interface ITokenizer
    {
        public bool HasMoreTokens();

        public void Advance();

        public TokenType TokenType();

        public KeyWord KeyWord();

        public char Symbol();

        public string Identifier();

        public int IntVal();

        public string StringVal();
    }
}
