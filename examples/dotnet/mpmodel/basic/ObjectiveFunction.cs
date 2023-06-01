using Google.OrTools.LinearSolver;

namespace Teste
{
    public static class ObjectiveFunction
    {
        public static Model.MakerDelegate Obj = new Model.MakerDelegate(MakeObjectiveFoo);

        public static void MakeObjectiveFoo(Model model)
        {
            var solver = model.GetSolver();
            var obj = model.GetObjectiveFunction();

            var x = model.GetVariablesFromMaker(Variables.A)[0];
            obj.SetMinimization();
            obj.SetCoefficient(x, 10);
        }
    }
}
