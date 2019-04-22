var StreamChecker = function(words) {
    this.root = {ch: '', ok: false, children: {}};
    this.hist = [];
    words.forEach(w => {
        this.add(w);
    });
};
StreamChecker.prototype.add = function(word){
    let node = this.root;
    for (var i = word.length - 1; i >= 0; i--) {
        var ch = word[i];
        if (!node.children[ch]) {
            node.children[ch] = {ch, ok: false, children: {}};
        }
        node = node.children[ch];
        node.ok = node.ok || i == 0;
    }
}
StreamChecker.prototype.query = function(letter){
    this.hist.unshift(letter);
    var node = this.root;
    for(var i=0; i<this.hist.length; i++){
        var ch = this.hist[i];
        if (node.children[ch])
            node = node.children[ch];
        else
            return false;
        if (node.ok)
            return true;
    }
    return false;
};
