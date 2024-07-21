namespace HackCompiler.JackAnalyzer
{
    internal class JackAnalyzer
    {
        public void Go(string inPath, string outPath)
        {
            string[] files = { inPath };

            if (Directory.Exists(inPath)) files = Directory.GetFiles(inPath, "*.jack");
            
            foreach (var file in files) ProcessFile(file, outPath); ;
        }

        private void ProcessFile(string f, string outPath)
        {
            using (FileStream fs = File.OpenRead(f))
            {
                var t = new Tokenizer.Tokenizer(fs);

                var ce = new CompilationEngine.CompilationEngine(t, File.OpenWrite(outPath + "\\" + Path.GetFileNameWithoutExtension(f) + ".xml"));

                ce.CompileClass();
            }
        }
    }
}