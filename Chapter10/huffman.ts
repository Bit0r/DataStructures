let raw = <{ [key: string]: number }>{
    A: 186, B: 64, C: 13, D: 22, E: 32, F: 103, G: 21, H: 15, I: 47, J: 57, K: 1, L: 2, M: 32,
    N: 20, O: 57, P: 63, Q: 15, R: 1, S: 48, T: 51, U: 80, V: 23, W: 8, X: 18, Y: 1, Z: 16
}

class Trnode {
    left: Trnode | null;
    right: Trnode | null;
    value: number;
    char: string;
    constructor(char: string, value: number, left: Trnode | null, right: Trnode | null) {
        this.left = left;
        this.right = right;
        this.value = value;
        this.char = char;
    }
}
class InitError extends Error { };
class InputError extends Error { };
class Huffman {
    root: Trnode | undefined;
    constructor(raw: { [key: string]: number }) {
        let forest: Trnode[] = [];
        let keys = Object.keys(raw);
        keys.forEach(key => {
            let node = new Trnode(key, raw[key], null, null);
            forest.push(node);
        })
        while (forest.length != 1) {
            forest.sort((a, b) => a.value - b.value);
            let root = new Trnode('', forest[0].value + forest[1].value, forest[0], forest[1])
            forest.shift();
            forest.shift();
            forest.push(root);
        }
        this.root = forest[0];
    }
    private _PrintCode(root: Trnode, code: string) {
        //Save the path into 'code'
        if (root.left == null) {
            let text = document.createTextNode(root.char + ':' + code);
            let p = document.createElement('p');
            p.appendChild(text);
            document.body.appendChild(p);
            return;
        }
        this._PrintCode(root.left, code + '0');
        this._PrintCode(<Trnode>root.right, code + '1');
    }

    print() {
        try {
            if (this.root == null)
                throw new InitError('Please initialize the Huffman tree');
            this._PrintCode(this.root, '');
        } catch (err) {
            if (err instanceof InitError)
                alert(err);
            else
                throw err;
        }
    }
    decode() {
        try {
            if (this.root == null)
                throw new InitError('Please initialize the Huffman tree');
            let current: Trnode | null;
            let code = <string>prompt('Please input the huffman code');
            for (current = this.root; current?.left != null && code != ''; code = code.slice(1)) {
                if (code[0] == '0')
                    current = (<Trnode>current).left;
                else
                    current = (<Trnode>current).right;
            }
            if (current?.left != null || code != '')
                throw new InputError('The huffman code is wrong!');
            alert('The decoded result is: ' + current?.char);
        } catch (err) {
            if (err instanceof InitError || err instanceof InputError)
                alert(err);
            else
                throw err;
        }
    }
}

let HT = new Huffman(raw);
HT.print();
HT.decode();