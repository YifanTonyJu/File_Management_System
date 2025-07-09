<template>
  <div>
    <router-link to="/">← Back</router-link>
    <h1>Query All Files</h1>
    
    <button @click="getAllFiles">Get All Files</button>

    <p v-if="message">{{ message }}</p>

    <div v-if="files.length > 0">
      <h3>File List:</h3>
      <div v-for="file in files" :key="file.file_name" class="file-item">
        <p><strong>Name:</strong> {{ file.file_name }}</p>
        <p><strong>Path:</strong> {{ file.file_path }}</p>
        <p><strong>Type:</strong> {{ file.file_type }}</p>
        <p><strong>Size:</strong> {{ file.file_size }} bytes</p>
        <p><strong>User ID:</strong> {{ file.user_id }}</p>
        <hr>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const message = ref('')
const files = ref([])

const getAllFiles = async () => {
  try {
    const response = await fetch('/api/files')
    
    if (!response.ok) {
      throw new Error('Failed to get files')
    }
    
    const data = await response.json()
    files.value = data.files
    message.value = 'Found ' + data.count + ' files'
    
  }
  catch (error) {
    message.value = `Error: ${error.message}`
  }
}
</script>

<style scoped>
div {
    text-align: center;
    padding: 20px;
}

button {
    margin: 10px;
    padding: 10px 20px;
    background: green;
    color: white;
    border: none;
}

router-link {
    color: blue;
    text-decoration: none;
}

.file-item {
    border: 1px solid #ccc;
    margin: 10px auto;
    padding: 10px;
    max-width: 500px;
    text-align: left;
}

p {
    margin: 5px 0;
}

hr {
    margin: 10px 0;
}
</style>