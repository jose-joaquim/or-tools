namespace Google.OrTools.LinearSolver
{
    using System;
    using System.Collections.Generic;

    public partial class Model
    {
        public delegate Variable[] VariableMakerDelegate(Model model);
        public delegate Constraint[] ConstraintMakerDelegate(Model model);

        public void RunVariableMakers()
        {
            for (int m = 0; m < GetNumberOfVariableMakers(); ++m)
            {
                VariableMakerDelegate _maker = GetVariableMaker(m);
                Variable[] vars = _maker(this);
                SetVariablesOfMaker(_maker, vars);
            }
        }

        public void RunConstraintMakers()
        {
            for (int m = 0; m < GetNumberOfConstraintMakers(); ++m)
            {
                ConstraintMakerDelegate _maker = GetConstraintMaker(m);
                Constraint[] constraints = _maker(this);
                SetConstraintsOfMaker(_maker, constraints);
            }
        }

        public void BuildModel()
        {
            Console.WriteLine("Building model...");
            RunVariableMakers();
            RunConstraintMakers();
            Console.WriteLine("Model built");
        }
    }
}
