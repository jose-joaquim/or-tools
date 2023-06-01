using Google.OrTools.LinearSolver;

namespace Teste
{
    public static class Constraints
    {
        public static Model.ConstraintMakerDelegate X = new Model.ConstraintMakerDelegate(
            MakeConstraintX
        );

        public static Constraint[] MakeConstraintX(Model model)
        {
            var solver = model.GetSolver();
            var x1 = model.GetVariablesFromMaker(Variables.A);
            var x2 = model.GetVariablesFromMaker(Variables.B);
            return new Constraint[] { solver.Add(2 * x2[0] + 3 * x1[0] >= 17) };
        }
    }
}
