package lr1;

import com.ibm.streams.operator.types.RString;

import com.ibm.streams.operator.OperatorContext;
import com.ibm.streams.operator.OutputTuple;
import com.ibm.streams.operator.Tuple;

public class ParserMachine extends AbstractParserMachine 
{

    @Override
    public void initialize(OperatorContext context) throws Exception 
    {
        super.initialize(context);
    }

    @Override
    protected void process0(IPort0 tuple) throws Exception 
    {
    	RString arithmeticExpressionSpl = tuple.get_arithmeticExpression();
    	String arithmeticExpressionJava = arithmeticExpressionSpl.getString();
    	
    	ArithmeticExpressionParserMachine arithmeticExpressionParserMachine = new ArithmeticExpressionParserMachine(arithmeticExpressionJava.length());
    	try
        {
            for (int i = 0; i < arithmeticExpressionJava.length(); ++i)
            {
            	arithmeticExpressionParserMachine.parse(arithmeticExpressionJava.charAt(i));
            }
        }
        catch (IllegalExpressionException exception)
        {
        	throw new RuntimeException(exception);
        }
    	
    	String treeAsXml = arithmeticExpressionParserMachine.getAst().getTreeAsXml();
    	
    	RString arithmeticExpressionTreeSpl = new RString(treeAsXml);
    	OPort0 arithmeticExpressionTreeTuple = getOutput0().newTuple();
    	arithmeticExpressionTreeTuple.set_arithmeticExpressionTree(arithmeticExpressionTreeSpl);
        submit0(arithmeticExpressionTreeTuple);
    }
}
