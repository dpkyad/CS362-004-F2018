import junit.framework.TestCase;


public class UrlValidatorTest extends TestCase {
	private final boolean printStatus = true;

   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   
 //You can use this function to implement your manual testing	  
   public void testManualTest(){
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   if (printStatus) {
	         System.out.println("testManualTest() ");
	    }
	   // Valid
	   assertTrue(urlVal.isValid("http://www.google.com"));
	   assertTrue(urlVal.isValid("ftp://255.255.255.255:65535/test1/"));
	   
	   assertTrue(urlVal.isValid("ftp://255.255.255.255:80/test1/?action=edit&mode=up"));
	   assertTrue(urlVal.isValid("http://go.com:80/$23"));
	   assertTrue(urlVal.isValid("h3t://www.google.com:0/test1/file?action=edit&mode=up"));
	   assertTrue(urlVal.isValid("ftp://255.com:80/test1?action=view"));
//	   // Invalid
	   assertFalse(urlVal.isValid("http:///www.google.com/"));
	   assertFalse(urlVal.isValid("://www.google.com"));
	   assertFalse(urlVal.isValid("://www.google.com:65535/test1?action=edit&mode=up"));
	   assertFalse(urlVal.isValid("http:/go.a:65a/test1"));
	   assertFalse(urlVal.isValid("http://go.au/../?action=edit&mode=up"));
	   assertFalse(urlVal.isValid("3ht://go.1aa:80/test1"));
	   assertFalse(urlVal.isValid("ftp://256.256.256.256:65535/test1/"));
   }
   
   // testUrlScheme
   public void testYourFirstPartition(){
	   System.out.println("testYourFirstPartition()");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   for(int index = 0; index < testUrlScheme.length; index++) {
	    	StringBuilder testBuffer = new StringBuilder();
	        boolean expected = true;
	        testBuffer.append(testUrlScheme[index].item);
	        testBuffer.append("www.google.com");
            expected &= testUrlScheme[index].valid;
            
	         String url = testBuffer.toString();
	         boolean result = urlVal.isValid(url);
//	         if(result == true){ 
	        	 System.out.println(url + ", result="+ result + ", expected=" + expected);
//	         }
	         assertEquals(url, expected, result);
	     }

   }
   //testUrlAuthority
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	
	   System.out.println("testYourSecondPartition()");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   // randomly generate a url
	   for(int index = 0; index < testUrlAuthority.length; index++) {
	    	StringBuilder testBuffer = new StringBuilder();
	    	testBuffer.append("http://");
	        boolean expected = true;
	        testBuffer.append(testUrlAuthority[index].item);
            expected &= testUrlAuthority[index].valid;
            
            String url = testBuffer.toString();
            boolean result = urlVal.isValid(url);
//            if(result == true){ 
//            	System.out.println(url);
//            }
            System.out.println(url + ", result="+ result + ", expected=" + expected);
	        assertEquals(url, expected, result);
	     }
   }
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   int test_count = 2000;// set the test count to run
	   System.out.println("testIsValid()");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   // randomly generate a url
	   for(int i = 0; i < test_count; i++) {
	      // randomize
	    	StringBuilder testBuffer = new StringBuilder();
	        boolean expected = true;
	        // for each partition, pick an item randomly
	        for (int testPartsIndex = 0; testPartsIndex < testUrlParts.length; ++testPartsIndex) {
	            ResultPair[] part = (ResultPair[]) testUrlParts[testPartsIndex]; // get the items in the partition
	            int index = (int) (Math.random() * part.length); // get a random number for index
	            testBuffer.append(part[index].item); // get the item for current partition
	            expected &= part[index].valid; // accumulate the expected result
	            //System.out.println("details "+ part[index].item + " " + part[index].valid);
	         }
	         String url = testBuffer.toString(); // create the url
	         boolean result = urlVal.isValid(url); // get result by our own defined validation function.
	         if(result == true){ 
	        	 System.out.println(url);
	         }
//	         if(result == true){ 
//	        	 System.out.println("true " + url);
//	         }else{
//	        	 System.out.println("false " + url);
//	         }
	         assertEquals(url, expected, result); // compare the expected output and actual result
	     }
   }
   /**
    * Only used to debug the unit tests.
    * @param argv
    */
   public static void main(String[] argv) {
	   UrlValidatorTest fct = new UrlValidatorTest("url test");
	   fct.testManualTest();
	   fct.testYourFirstPartition();
	   fct.testYourSecondPartition();
	   fct.testIsValid();
   }
   ResultPair[] testUrlScheme = {
		   new ResultPair("http/", false),
		   new ResultPair("http:/", false),
		   new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:", false),
           new ResultPair("://", false)
           };

	ResultPair[] testUrlAuthority = {
			new ResultPair("www.google.com", true),
			new ResultPair("go.com", true),
			new ResultPair("go.au", true),
			new ResultPair("0.0.0.0", true),
			new ResultPair("255.255.255.255", true),
			new ResultPair("256.256.256.256", false),
			new ResultPair("255.com", true),
			new ResultPair("1.2.3.4.5", false),
			new ResultPair("1.2.3.4.", false),
			new ResultPair("1.2.3", false),
			new ResultPair(".1.2.3.4", false),
			new ResultPair("go.a", false),
			new ResultPair("go.a1a", false),
			new ResultPair("go.1aa", false),
			new ResultPair("aaa.", false),
			new ResultPair(".aaa", false),
			new ResultPair("aaa", false),
			new ResultPair("", false)
	};
	ResultPair[] testUrlPort = {
			new ResultPair(":80", true),
	        new ResultPair(":65535", true),
	        new ResultPair(":0", true),
	        new ResultPair("", true),
	        new ResultPair(":-1", false),
	        new ResultPair(":65636",false),
	        new ResultPair(":65a", false)
	};
	ResultPair[] testPath = {
			new ResultPair("/test1", true),
			new ResultPair("/t123", true),
			new ResultPair("/$23", true),
			new ResultPair("/..", false),
			new ResultPair("/../", false),
			new ResultPair("/test1/", true),
			new ResultPair("", true),
			new ResultPair("/test1/file", true),
			new ResultPair("/..//file", false),
			new ResultPair("/test1//file", false)
	};
	//Test allow2slash, noFragment
	ResultPair[] testUrlPathOptions = {
			new ResultPair("/test1", true),
            new ResultPair("/t123", true),
            new ResultPair("/$23", true),
            new ResultPair("/..", false),
            new ResultPair("/../", false),
            new ResultPair("/test1/", true),
            new ResultPair("/#", false),
            new ResultPair("", true),
            new ResultPair("/test1/file", true),
            new ResultPair("/t123/file", true),
            new ResultPair("/$23/file", true),
            new ResultPair("/../file", false),
            new ResultPair("/..//file", false),
            new ResultPair("/test1//file", true),
            new ResultPair("/#/file", false)
	};
	
	ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
	          new ResultPair("?action=edit&mode=up", true),
	          new ResultPair("", true)
	};
	Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};

}
