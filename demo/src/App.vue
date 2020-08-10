<template>
  <div id="app">
    <input type="file" ref="files" v-on:change="fileChanged" class="input is-primary" />
    <a v-on:click="generateSvg" class="button is-primary"> 生成流程图 </a>
  </div>
</template>

<script>
export default {
  name: 'App',
  methods: {
    fileChanged() {
      let input_dom = this.$refs.files;
      this.file = input_dom.files[0];

      let reader = new FileReader();
      reader.onload = () => {
        this.parseFileContent(reader.result);
      }
      console.log("reading file ...");
      reader.readAsText(this.file, 'utf8');
    },
    parseFileContent(content) {
      console.log('parsing content ...');
      let parser = new DOMParser();
      let xmldoc = parser.parseFromString(content, 'text/xml');

      let persons = xmldoc.getElementsByTagName('Person');

      this.persons = [];
      for (let i = 0; i < persons.length; ++i) {
        this.persons.push({
          name: persons[i].getElementsByTagName('name')[0].textContent,
          age: persons[i].getElementsByTagName('age')[0].textContent
        });
      }
      console.log('parsing content OK!');
    },
    generateSvg() {
      console.log(this.persons);
      if (this.persons.length == 0) {
        window.alert("Invalid file!");
        return;
      }
    }
  },
  components: {
  },
}
</script>

<style>
/* #app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
} */
</style>
