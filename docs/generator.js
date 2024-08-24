async function generate() {
	let data = await fetch("target.md");
	console.log(data);
	document.getElementById('content').innerHTML = marked.parse();
	hljs.highlightAll();
}

generate();
