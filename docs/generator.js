async function generate() {
	//get the markdown file
	let md_file = await fetch("target.md");

	//convert data into string
	let data = await md_file.text();

	//convert markdown string into html
	document.getElementById('content').innerHTML = marked.parse(data);

	//syntax highlight code blocks
	hljs.highlightAll();
}

generate();
