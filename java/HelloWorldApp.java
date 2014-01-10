import java.io.*;
import java.util.regex.Pattern;
import java.util.*;

class HelloWorldApp {

    static Hashtable<String, Integer> stringToOccurence;
    static Hashtable<Integer, String[]> occurenceToStrings;

    public static void main(String[] args) {
        System.out.println("Hello World!"); // Display the string.
        ComputeWordToOccurenceFromAFile();
        PrintWordToOccurence();
    }

    public static void ComputeWordToOccurenceFromAFile()
    {
        File file = new File("toto.txt");
        Pattern word = Pattern.compile("[^A-Z^a-z]+");
        BufferedReader reader = null;
        stringToOccurence = new Hashtable<String, Integer>();

        try {
            
            reader = new BufferedReader(new FileReader(file));
            String text = null;
            text = reader.readLine();

            while(text != null)
            {
                String[] parts = word.split(text);
               
                for(int x = 1; x <parts.length; x=x+1) {
                   
                    Integer occurence = stringToOccurence.get(parts[x]);
                    if (occurence == null)
                    {
                        stringToOccurence.put(parts[x], 1);
                    }
                    else
                    {
                        occurence = occurence+1;
                        stringToOccurence.put(parts[x], occurence);

                    }
                }

                text = reader.readLine();
                
            }
             
        }

        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        } 
        finally {

            try {
                if (reader != null)
                {
                    reader.close();
                }
            } 
            catch(IOException e) {
            }
        }
    }
    
    static void PrintWordToOccurence()
    {
        for (Map.Entry<String, Integer> entry : stringToOccurence.entrySet())
        {
            System.out.println(entry.getKey() + "/" + entry.getValue());
        }
    }

    public static void ComputeOccurenceToWordFromAFile()
    {
        for (Map.Entry<String, Integer> entry : stringToOccurence.entrySet())
        {
            Integer occurence = entry.getValue();
          
            Integer occurencePair = occurenceToString.get(occurence);

            if (occurencePair == null)
            {
                occurenceToStrings.put(occurencePair, 1);
            }
            else
            {
              
                occurenceToStrings.put(parts[x], occurence);                
            }
        }
    }

}