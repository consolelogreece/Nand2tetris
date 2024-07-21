using HackCompiler.JackAnalyzer;

var analyzer = new JackAnalyzer();

if (args.Length <= 1)
{
    Console.WriteLine("Correct usage: <input file or directory> <output directory>");
    return;
}
    
if (Path.Exists(args[0]))
{
    analyzer.Go(args[0], args[1]);
}