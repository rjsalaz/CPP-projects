import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;


public class LeastRecentlyUsed
{
    private  String referenceString;
    private  int numOfPageFrames;

    // set is used to look up values and for it use of unique values 
    // hash map is used to track page element and its index
    private  HashSet<String> setOfPages;
    private  HashMap<String, Integer> mapOfPages = new HashMap<String, Integer>();

    private int pageFaults = 0;
    private int maxValue;
    private int minvalue;
    
    public LeastRecentlyUsed(String numOfPageframesPar, String referenceStringPar)
    {

        this.numOfPageFrames = Integer.parseInt(numOfPageframesPar);
        this.referenceString = referenceStringPar;
        setOfPages = new HashSet<String>(this.numOfPageFrames);

    }

    public String RunAlgo()
    {
    	
	   	display(); 
    	
	   	// Run Through the whole reference String
        for( int i = 0; i < referenceString.length(); i++ )
        {
        	String currentPage = Character.toString(referenceString.charAt(i));

        	System.out.print("\t\t" + currentPage + "\t");
        	
        	// Check if the current set is less then the max size
            if( setOfPages.size() < numOfPageFrames )
            {
            	// if set dose not have current page add it 
                if( !setOfPages.contains(currentPage) )
                {
                	//Add current page to set 
                    setOfPages.add(currentPage);
                    pageFaults++; 
                    
                    System.out.print("\t* Page Fault Occured: " + currentPage + " added *\t\t\t");
                }
                else       
                {
               	 System.out.print("\t* No Page Fault Occured *\t\t\t");
                }

                // Add the currentPage and its index to the map 
                mapOfPages.put(currentPage, i);
                
            }
            else
            {
            	 //Check if the currentPage is in the set
            	 // if not replace it with the least used value
                if( !setOfPages.contains(currentPage) )
                {

                    maxValue = Integer.MAX_VALUE;
                    minvalue = Integer.MIN_VALUE;
                    
                    Iterator<String> itr = setOfPages.iterator();

                    //Find the least recently used value within the map
                    while( itr.hasNext())
                    {
                        // Get a value from the set
                        int temp = Integer.parseInt(itr.next()); 
                        
                        // find the page within the map that has the smallest index
                        // using the value from the set 
                        if(mapOfPages.get(Integer.toString(temp)) < maxValue)
                        { 
                            maxValue = mapOfPages.get(Integer.toString(temp));
                            minvalue = temp; 
                        }

                    }

                    // remove the least used value from the set and map
                    setOfPages.remove(Integer.toString(minvalue));
                    mapOfPages.remove(Integer.toString(minvalue));

                    // add the current page to the set 
                    setOfPages.add(currentPage);
                    
                    pageFaults++;
                    
                    System.out.print("\t* Page Fault Occured: " + currentPage + " added, " + Integer.toString(minvalue) + " removed *\t");

                }
                else       
                {
               	 System.out.print("\t* No Page Fault Occured *\t\t\t");
                }
                
                // Add the currentPage and its index to the map              
                mapOfPages.put(currentPage, i);

            }
            
            System.out.print(setOfPages + "\t");
            System.out.println();

        }
        
        System.out.println("\n\tTotal Page Faults: " + Integer.toString(pageFaults) + "\n");
        
        return Integer.toString(pageFaults); 

    }
    
    // Display current reference string and pageFrames size
    private void display()
    {
    	System.out.println("\t**************************** LEAST RECENTLY USUED AlGORITHM****************************" ); 
	   	System.out.println("\tReference String: " + referenceString + "\t\tPage Frames: " + numOfPageFrames);
	   	System.out.println();
	   	 
	   	System.out.println("\tCurrent Page Frame" + "\t\t\tPages Fault" + "\t\t\tPage Frame Content");
	   	System.out.println("\t_________________________________________________________________________________________");
    }
    
}
