#pragma once

#include "file/filepath.hpp"


namespace Base
{
    struct ResourceLoadException : public runtime_error
    {
        ResourceLoadException(const string& message) : runtime_error(message) {};
    };

    /* A processed item in the "res" folder of the project. */
    class ResourceHandler;
    class Resource
    {
      friend ResourceHandler;

      protected:
        /* Loads the resource from an external file or
           internal memory. */
        virtual void load(const FilePath& file) = 0;
        virtual void load(const FileData& file) = 0;
        
        /* Implemented by reload-able children only when dynamic resources
           are enabled and the associated file is changed on the disk.
           Returns whether the resource was successfully reloaded. */ 
        virtual bool reload(const FilePath& file) { return false; };

        /* Checks whether the file data should be loaded. */
        bool checkLoad();

        /* Creates a new resource. */
        static Base::Resource* createDynamic(const string& name, FilePath file);
        static Base::Resource* createInternal(const string& name, FileData data);

        bool isLoaded = false;

      private:
        static Base::Resource* create(const string& fileExt);
        FileData data;

        bool     isDynamic;
        FilePath dynamicFile;
        uint     dynamicLastChange;
    };
    
    /* A good ol' fashioned text file. */
    class TextFile : public Resource
    {
      public:
        TextFile() {};
        void load(const FilePath& file) override;
        void load(const FileData& data) override;
        string text;
    };
}