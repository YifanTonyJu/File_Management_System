<template>
  <div>
    <h1>File Management System</h1>
    
    <div class="section">
      <h2>File Operations</h2>
      <div>
        <router-link to="/add">Add File</router-link>
        <router-link to="/delete">Delete File</router-link>
        <router-link to="/update">Update File</router-link>
      </div>
    </div>
    
    <div class="section">
      <h2>Query Operations</h2>
      <div>
        <router-link to="/query">Query All Files</router-link>
        <router-link to="/query-user">Query by User</router-link>
        <router-link to="/query-file">Query by File Name</router-link>
      </div>
    </div>
  </div>
</template>

<script setup>
</script>

<style scoped>
div {
  text-align: center;
  padding: 20px;
}

h1 {
  margin-bottom: 30px;
}

h2 {
  margin: 20px 0;
  color: #333;
}

.section {
  margin-bottom: 40px;
  padding: 20px;
  border: 1px solid #ddd;
  border-radius: 10px;
}

a {
  display: inline-block;
  margin: 10px;
  padding: 15px 30px;
  background-color: #007bff;
  color: white;
  text-decoration: none;
  border-radius: 5px;
}

a:hover {
  background-color: #0056b3;
}
</style>
