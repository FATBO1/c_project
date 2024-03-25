#ifndef escape_barchart_h
#define escape_barchart_h

char *escape_barchart_forJSON(const char *input)
    {
        int newLen = 0;
        for (int i = 0; input[i]; i++)
        {
            switch (input[i])
            {
            case '\n':
                newLen += 2;
                break; // "\n" becomes "\\n"
            case '\\':
                newLen += 2;
                break; // "\\" becomes "\\\\"
            default:
                newLen++;
            }
        }

        char *escaped = malloc(newLen + 1);
        if (!escaped)
            return NULL;

        for (int i = 0, j = 0; input[i]; i++)
        {
            switch (input[i])
            {
            case '\n':
                escaped[j++] = '\\';
                escaped[j++] = 'n';
                break;
            case '\\':
                escaped[j++] = '\\';
                escaped[j++] = '\\';
                break;
            default:
                escaped[j++] = input[i];
            }
        }
        escaped[newLen] = '\0';
        return escaped;
    }

#endif