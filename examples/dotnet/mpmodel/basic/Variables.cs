using Google.OrTools.LinearSolver;

namespace Teste
{
    public static class Variables
    {
        public static Model.VariableMakerDelegate A = new Model.VariableMakerDelegate(
            Variables.MakeVariableA
        );
        public static Model.VariableMakerDelegate B = new Model.VariableMakerDelegate(
            Variables.MakeVariableB
        );

        public static Variable[] MakeVariableA(Model model)
        {
            var solver = model.GetSolver();
            return new Variable[] { solver.MakeIntVar(0.0, double.PositiveInfinity, "x1") };
        }

        public static Variable[] MakeVariableB(Model model)
        {
            var solver = model.GetSolver();
            return new Variable[] { solver.MakeIntVar(0.0, double.PositiveInfinity, "x2") };
        }
    }
}
