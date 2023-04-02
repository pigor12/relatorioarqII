import java.io.File;
import java.util.Map;
import java.util.HashMap;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;

public class Conversor
{
    private static final Map<String, String> OPCODES = new HashMap<>();
    static
    {
        OPCODES.put("An", "0");
        OPCODES.put("nAoB", "1");
        OPCODES.put("AnB", "2");
        OPCODES.put("zeroL", "3");
        OPCODES.put("nAeB", "4");
        OPCODES.put("Bn", "5");
        OPCODES.put("AxB", "6");
        OPCODES.put("ABn", "7");
        OPCODES.put("AnoB", "8");
        OPCODES.put("nAxB", "9");
        OPCODES.put("copiaB", "A");
        OPCODES.put("AB", "B");
        OPCODES.put("umL", "C");
        OPCODES.put("AoBn", "D");
        OPCODES.put("AoB", "E");
        OPCODES.put("copiaA", "F");
    }

    private static String getOpcode(String mnemonico)
    {
        return OPCODES.getOrDefault(mnemonico, "0");
    }

    public static void main(String[] args) throws IOException
    {
        File arquivoULA = new File("testeula.ula");
        File arquivoHEX = new File("testeula.hex");

        Scanner leitor = new Scanner(arquivoULA);
        FileWriter escritor = new FileWriter(arquivoHEX);

        String x = null;
        String y = null;
        String w = null;
        boolean mod = false;

        while (leitor.hasNextLine())
        {
            String linha = leitor.nextLine();
            if (!linha.contains("inicio:") && linha.length() >= 4)
            {
                String var = linha.substring(0, 1);
                String valor = linha.substring(linha.indexOf("=") + 1, linha.indexOf(";")).trim();
                switch (var)
                {
                    case "X":
                    {
                        x = valor;
                        break;
                    }
                    case "Y":
                    {
                        y = valor;
                        break;
                    }
                    case "W":
                    {
                        w = getOpcode(valor);
                        mod = true;
                        break;
                    }
                }
            }

            if (x != null && y != null && w != null && mod)
            {
                escritor.write(x + y + w + "\n");
                mod = false;
            }
        }
        leitor.close();
        escritor.close();
    }
}
