type AutocompleteSystem struct {
	sentences   []string
	times       []int
	sentenceMap map[string]int
	input       string
}
func Constructor(sentences []string, times []int) AutocompleteSystem {
	sentenceMap := make(map[string]int)
	for i := 0; i < len(sentences); i++ {
		sentenceMap[sentences[i]] = i
	}
	return AutocompleteSystem{sentences, times, sentenceMap, ""}
}
func (this *AutocompleteSystem) Input(c byte) []string {
	if c == '#' {
		recordInput(this)
		return []string{}
	}
	this.input += string(c)
	input      := this.input
	words      := this.sentences
	res        := make([]int, 3)
	res[0], res[1], res[2] = -1, -1, -1
	for i, sent := range words {
		if !strings.HasPrefix(sent, input) {
			continue
		}
		if res[0] == -1 || less(this, sent, words[res[0]]) {
			res[0], res[1], res[2] = i, res[0], res[1]
		}
                else if res[1] == -1 || less(this, sent, words[res[1]]) {
			res[1], res[2] = i, res[1]
		}
                else if res[2] == -1 || less(this, sent, words[res[2]]) {
			res[2] = i
		}
	}
	output := make([]string, 0, 3)
	for i := 0; i < len(res); i++ {
		if res[i] < 0 {
			break
		}
		output = append(output, words[res[i]])
	}
	return output
}
func less(this *AutocompleteSystem, a string, b string) bool {
	x := this.times[this.sentenceMap[a]]
	y := this.times[this.sentenceMap[b]]
	if x > y {
		return true
	}
	if x == y {
		return a < b
	}
	return false
}
func recordInput(this *AutocompleteSystem) {
	input := this.input
	if len(input) == 0 {
		return
	}
	if i, found := this.sentenceMap[input]; found {
		this.times[i]++
	}
        else {
		this.sentences          = append(this.sentences, input)
		this.times              = append(this.times, 1)
		this.sentenceMap[input] = len(this.sentences) - 1
	}
	this.input = ""
}



















