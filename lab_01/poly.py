import itertools
class Polynominal:
    def __init__(self, size, coef):
        self.size = size
        self.coef = []
        for a in coef:
            self.coef.append(a)

    def __str__(self):
        cur_str = ""
        for a in self.coef:
            cur_str += (str(round(a, 8)) + " ")
        return cur_str
    
    def __add__(self, other):
        result = [a + b for a, b in itertools.zip_longest(self.coef, other.coef, fillvalue=0)]
        
        return (Polynominal(len(result), result))

    
    
    def __mul__(self, other):
        _self = self.coef
        _other = other.coef
        result = [0] * (len(_self) + len(_other) - 1)
        for selfpow, selfco in enumerate(_self):
            for otherpow,otherco in enumerate(_other):
                result[selfpow + otherpow] += selfco * otherco
        
        return (Polynominal(len(result), result))

    def integrate(self):
        self.coef.insert(0, 0)
        for i in range(1, len(self.coef)):
            self.coef[i] = self.coef[i] / (i)
        return self
            
