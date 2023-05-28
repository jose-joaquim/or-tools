namespace Google.OrTools.LinearSolver
{
    using System;
    using System.Collections.Generic;

    public partial class Model
    {
        public delegate void MakerDelegate(Model model);
        public delegate Variable[] VariableMakerDelegate(Model model);
        public delegate Constraint[] ConstraintMakerDelegate(Model model);

        public void RunVariableMakers()
        {
            Console.WriteLine("Running Variable Makers");
            for (int m = 0; m < GetNumberOfVariableMakers(); ++m)
            {
                VariableMakerDelegate _maker = GetVariableMaker(m);
                Variable[] vars = _maker(this);
                SetVariablesOfMaker(_maker, vars);
            }
        }

        public void RunConstraintMakers()
        {
            Console.WriteLine("Running Constraint Maker");
            for (int m = 0; m < GetNumberOfConstraintMakers(); ++m)
            {
                ConstraintMakerDelegate _maker = GetConstraintMaker(m);
                Constraint[] constraints = _maker(this);
                SetConstraintsOfMaker(_maker, constraints);
            }
        }

        public void RunObjectiveFunctionMaker()
        {
            Console.WriteLine("Running Objective Function Maker");
            MakerDelegate objectiveDelegate = GetObjectiveFunctionMaker();
            objectiveDelegate(this);
        }

        public void AddVariableMakers(params VariableMakerDelegate[] makers)
        {
            for (int m = 0; m < makers.Length; ++m)
                AddVariableMaker(makers[m]);
        }

        public void AddConstraintMakers(params ConstraintMakerDelegate[] makers)
        {
            for (int m = 0; m < makers.Length; ++m)
                AddConstraintMaker(makers[m]);
        }

        public void BuildModel()
        {
            Console.WriteLine("Start build model");
            RunVariableMakers();
            RunConstraintMakers();
            RunObjectiveFunctionMaker();
            SetBuildStatus(true);
            Console.WriteLine("Model built");
        }
    }
}
