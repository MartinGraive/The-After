/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

class StringPrimitives
{
    public:
        static std::vector<std::wstring> split(std::wstring str, char delimiter = ' ', bool keep_delimiter = false) {
            std::vector<std::wstring> result;
            int lastpos = 0;
            for (unsigned int i = 0 ; i < str.size() ; i++) {
                if (str[i] == delimiter) {
                    if (keep_delimiter) {result.push_back(str.substr(lastpos, i - lastpos + 1));}
                    else {result.push_back(str.substr(lastpos, i - lastpos));}
                    lastpos = i + 1;
                }
            }
            result.push_back(str.substr(lastpos, str.size() - lastpos));

            return result;
        }
};
