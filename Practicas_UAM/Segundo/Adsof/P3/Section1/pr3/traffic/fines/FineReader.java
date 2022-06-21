package pr3.traffic.fines;

import java.util.*;

import java.io.*;

/**
 * This class reads the fines from a .txt file
 */
public abstract class FineReader {
    /**
     * This function reads the fines .txt and creates Fines with the corresponding attributes
     * @param file The .txt file that contains the fines 
     * @return An array with the fines created from the file
     */
    public static ArrayList<Fine> read(String file) {
        try {
            BufferedReader buffer = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
            String line;
            ArrayList<Fine> fines = new ArrayList<>();
            while((line = buffer.readLine()) != null){
                String[] parts = line.split("\\;");
                fines.add(new Fine(parts[0], parts[1], parts[2]));
            } 
            buffer.close();
            return fines;
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }
}
