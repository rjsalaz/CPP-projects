import java.util.ArrayList;

public class OptimalAlgorithm 
{

    private  String referenceString;
    private  int numOfPageFrames;
    private ArrayList<String> listOfPages = new ArrayList<String>(); 
    private int pageFaults = 0;
    


    public OptimalAlgorithm(String numOfPageframesPar, String referenceStringPar)
    {
        this.numOfPageFrames =  Integer.parseInt(numOfPageframesPar);
        this.referenceString = referenceStringPar;
    }

    
    public String RunAlgo()
    {	
    	display();
    	
    	// Run Through the whole reference String
    	for( int i = 0; i < referenceString.length(); i++)
    	{
    		String currentPage = Character.toString(referenceString.charAt(i));
    		System.out.print("\t\t" + currentPage + "\t");
    		
    		// Check if the current set is less then the max size
    		if( listOfPages.size() < numOfPageFrames)
    		{
    			listOfPages.add(currentPage);
    			pageFaults++;
    			
    			System.out.print("\t* Page Fault Occured: " + currentPage + " added *\t\t\t");
    			
    		}
    		// If value is already present jump to next page
    		else if( listOfPages.contains(currentPage) )
    		{
    			
    			System.out.print("\t* No Page Fault Occured *\t\t\t");
                System.out.print(listOfPages.toString() + "\t");
                System.out.println();
    			continue;
    			
    		}
    		//Find the value to be replaced 
    		else
    		{
    			// find the index of the value to be replaced and grab it from the reference string
    			int replaceValueIndex = findFarthestUnusedValue(i);     			
    			String pageToBeRemoved = Character.toString(referenceString.charAt(replaceValueIndex));
    			  			
    			// look through the page frame to find the page to be removed 
    			for(int j = 0; j < listOfPages.size(); j++)
    			{
    				
    				String stringFromPages = listOfPages.get(j);
    				
    				//remove page from page frame and add the current page
    				if( stringFromPages.equals(pageToBeRemoved))
    				{
    					listOfPages.remove(j); 			
    	    			listOfPages.add(currentPage); 
    					pageFaults++;
    						
    					System.out.print("\t* Page Fault Occured: " + currentPage + " added, " + pageToBeRemoved + " removed *\t");
    	    					
    					break;
    				}
    				
    			}		
    		}
    		
            System.out.print(listOfPages.toString() + "\t");
            System.out.println();
    	}
    	
        System.out.println("\n\tTotal Page Faults: " + Integer.toString(pageFaults) + "\n");
        
        return Integer.toString(pageFaults);
    }
    
    
     // Display current reference string and pageFrames size
    private void display()
    {
	   	System.out.println("\t************************************* OPTIMAL AlGORITHM *************************************" ); 
	   	System.out.println("\tReference String: " + referenceString + "\t\tPage Frames: " + numOfPageFrames);
	   	System.out.println();
	   	 
	   	System.out.println("\tCurrent Page Frame" + "\t\t\tPages Fault" + "\t\t\tPage Frame Content");
	   	System.out.println("\t_________________________________________________________________________________________");
    }
    
    
    
    
	private int findFarthestUnusedValue(int currentIndex)
	{
		int farthestIndex = 0;
		// Append a value to end of the reference string to mark it's end
		String referenceStringToCheck = referenceString + "9" ; 
				
		
		// Parse through the page frame and the current index of the reference string to the end of both
		// To find the index of a page from the page frame that is farthest away in the reference sting 
		for(int i = 0; i < listOfPages.size(); i++ )
		{	
			for(int j = currentIndex; j < referenceStringToCheck.length(); j++ )
			{
				 // Grab a page from the reference string and page frame
				 String stringFromPages = listOfPages.get(i);
				 String stringFromRef = Character.toString(referenceStringToCheck.charAt(j));		
			
				// if they are equal update the farthest index
				// only find the first occurrence of a page within the reference String
				if( stringFromPages.equals(stringFromRef) )
				{
				
					if( j > farthestIndex  )
					{			
						farthestIndex = j;	
					}
					
					break;
				}
				// If the value no longer exists in the reference string 
				// then this is the value we want to replace 
				else if(stringFromRef.equals("9"))
				{
					return referenceString.lastIndexOf(stringFromPages);
					
				}		
			}		
		}
		
		return farthestIndex;

	}
	
}
