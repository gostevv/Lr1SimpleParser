package lr1;

import java.io.ByteArrayOutputStream;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.annotation.*;

@XmlRootElement
public class AbstractSyntaxTree 
{

    public AbstractSyntaxTree()
    {
        
    }
     
    public AbstractSyntaxTree add(Lexem lexem)
    {
        if (Lexem.NUMBER.equals(lexem))
        {
            if (right == null)
            {
                right = new AbstractSyntaxTree();
                right.head = lexem;
            } 
            else if (left == null)
            {
                left = new AbstractSyntaxTree();
                left.head = lexem;
            }
        } 
        else if (Lexem.isOperation(lexem))
        {
            if (head == null)
            {
                head = lexem;
            }
            else 
            {
                AbstractSyntaxTree ast = new AbstractSyntaxTree();
                ast.right = this;
                ast.head = lexem;
                return ast;
            }
        }
        return this;
    }
    
    public AbstractSyntaxTree add(AbstractSyntaxTree ast)
    {
    	if (head == null)
        {
            head = ast.head;
            left = ast.left;
            right = ast.right;
        }
        else if (right == null)
        {
            right = ast;
        }
        else if (left == null)
        {
            left = ast;
        }
        return this;
    }
    
    public String getTreeAsXml() throws JAXBException
    {
        JAXBContext jaxbContext = JAXBContext.newInstance(AbstractSyntaxTree.class);
        Marshaller jaxbMarshaller = jaxbContext.createMarshaller();
        jaxbMarshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
        
        ByteArrayOutputStream treeInBytes = new ByteArrayOutputStream();
        jaxbMarshaller.marshal(this, treeInBytes);
        return treeInBytes.toString();
    }
    
    @XmlElement
    public AbstractSyntaxTree getLeftAbstractSyntaxTree()
    {
    	return left;
    }
    
    @XmlElement
    public AbstractSyntaxTree getRightAbstractSyntaxTree()
    {
    	return right;    	
    }
    
    @XmlElement
    public Lexem getHead()
    {
    	return head;
    }
    
    private Lexem head = null;
    
    private AbstractSyntaxTree left = null;
    private AbstractSyntaxTree right = null;
}
